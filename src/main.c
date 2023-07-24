#include "../inc/sender.h"
pid_t g_pid;
// Structure pour les opérations P() et V() sur les sémaphores
struct sembuf P = {0, -1, SEM_UNDO}; // Opération P (wait)
struct sembuf V = {0, 1, SEM_UNDO};	 // Opération V (signal)

void usage()
{
	printf("Usage : ");
	printf("data_sender \"Path/To/Midi/Folder\" \"Path/To/Midi/Folder_Redundancy\"\n");
	exit(0);
}

/**
 * @brief Create file path if doesnt exists
 * @param [file_path] File path /!\ cant be const /!\
 * @param [mode] Permission bit masks for mode
 */
int make_path(char *file_path, mode_t mode)
{
	for (char *p = strchr(file_path + 1, '/'); p; p = strchr(p + 1, '/'))
	{
		*p = '\0';
		if (mkdir(file_path, mode) == -1)
		{
			if (errno != EEXIST)
			{
				*p = '/';
				return -1;
			}
		}
		*p = '/';
	}
	return 0;
}

/**
 * @brief Called when signal "SIGINT" is sended
 * @param [signal] Signal Number (Probably 15)
 */
void close_child(int signal)
{
	printf("Killing child\n");
	(void)signal;
	kill(g_pid, SIGINT);
	exit(0);
}

/**
 * argv[1] = data_files_path
 * argv[2] = midi_files_path
 */
int main(int argc, char **argv)
{
	char *midi_file_path;			 // Pointeur vers le chemin du dossier des fichiers MIDI
	char *midi_file_path_redundancy; // Pointeur vers le chemin du dossier de redondance des fichiers MIDI

	if (argc == 3)
	{
		midi_file_path = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 2));
		sprintf(midi_file_path, "%s/", argv[1]);
		midi_file_path_redundancy = (char *)malloc(sizeof(char) * (strlen(argv[2]) + 2));
		sprintf(midi_file_path_redundancy, "%s/", argv[2]);
	}
	else
	{
		midi_file_path = (char *)malloc(sizeof(char) * (sizeof("./Space_MIDI/midi_files/") + 1));
		midi_file_path = strcpy(midi_file_path, "./Space_MIDI/midi_files/");

		midi_file_path_redundancy = (char *)malloc(sizeof(char) * (sizeof("./Space_MIDI/midi_files_redundancy/") + 1));
		midi_file_path_redundancy = strcpy(midi_file_path_redundancy, "./Space_MIDI/midi_files_redundancy/");
	}

	// Création d'un nouveau processus en utilisant la fonction fork()
	g_pid = fork();
	printf("PID : %d\n", g_pid);

	// Création des répertoires du chemin du dossier de données (midi_file_path)
	make_path(midi_file_path, 0755);

	if (g_pid == 0)
	{
		/**
		 * Default path :
		 * execl("../Space_MIDI/midi_controller", "midi_controller",\
		 *  "../Space_MIDI/midi_files", "../Space_MIDI/midi_files_redundancy", NULL);
		 */

		execl("./Space_MIDI/midi_controller", "midi_controller",
			  midi_file_path, midi_file_path_redundancy, NULL);

		exit(1);
	}

	signal(SIGINT, (void (*)(int))close_child);

	t_circular_buffer *buffer;

	buffer = (t_circular_buffer *)malloc(sizeof(t_circular_buffer));

	// Création du sémaphore
	int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
	if (semid == -1)
	{
		perror("semget");
		exit(1);
	}
	// Initialisation du sémaphore à 1 (disponible)
	if (semctl(semid, 0, SETVAL, 1) == -1)
	{
		perror("semctl");
		exit(1);
	}

	// Création et attachement à la mémoire partagée
	int shmid;
	struct shmseg *shmp;
	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644 | IPC_CREAT);

	if (shmid == -1)
	{

		printf("Error code :%d \n", errno);
		perror("Shared memory");
		return 1;
	}

	shmp = shmat(shmid, NULL, 0);
	if (shmp == (void *)-1)
	{
		perror("Shared memory attach");
		return 1;
	}

	int max_steps = SAMPLES_NU;
	int current_step = 0;

	int number_of_data_steps = (sizeof(g_all_data) / sizeof(t_data *)) - 1;

	int current_data_step_min = 0;
	int current_data_step_max = 0;

	int buffer_index = 0;

	bzero(buffer, sizeof(t_circular_buffer));
	for (int i = 0; i < SAMPLES_NU; i++, current_step++)
	{

		buffer_index = i % BUFFER_ROUNDS;
		buffer->older_block = (i + 1) % BUFFER_ROUNDS;
		int n = 1;

		n = ((number_of_data_steps)*current_step / max_steps) + 1;
		float duty;
		current_data_step_min = (max_steps / number_of_data_steps) * (n - 1);
		current_data_step_max = (max_steps / number_of_data_steps) * (n);

		duty = ((float)current_step - current_data_step_min) / (current_data_step_max - current_data_step_min);

		for (int u = 0; u < DATAS_SIZE; u++)
		{

			if (g_all_data[n - 1][u].data_type == FLOATING)
			{
				// Pointeur vers l'emplacement mémoire où stocker les données FLOATING dans le buffer circulaire
				float *ptr = (float *)((uint64_t)&buffer->data[buffer_index] + g_all_data[n - 1][u].offset);
				// Calcul de l'interpolation des données FLOATING et copie dans le buffer
				float data = (float)(g_all_data[n - 1][u].float_data * (1 - duty) + g_all_data[n][u].float_data * duty);
				memcpy(ptr, &data, sizeof(float));
				// Calcul de la variation aléatoire et ajout dans le buffer
				float tmpdelta = g_all_data[n - 1][u].float_delta * (1 - duty) + g_all_data[n][u].float_delta * duty;
				if (tmpdelta > 0)
				{
					*ptr += fmod((float)rand() / 13., tmpdelta * 2) - (tmpdelta);
				}
			}
			else if (g_all_data[n - 1][u].data_type == INTEGER)
			{
				// Pointeur vers l'emplacement mémoire où stocker les données INTEGER dans le buffer circulaire
				uint32_t *ptr = (uint32_t *)((uint64_t)&buffer->data[buffer_index] + g_all_data[n - 1][u].offset);
				// Calcul de l'interpolation des données INTEGER et copie dans le buffer
				uint32_t data = (uint32_t)(g_all_data[n - 1][u].int_data * (1 - duty) + g_all_data[n][u].int_data * duty);
				memcpy(ptr, &data, sizeof(uint32_t));
				// Calcul de la variation aléatoire et ajout dans le buffer
				int tmpdelta = (int)g_all_data[n - 1][u].int_delta * (1 - duty) + g_all_data[n][u].int_delta * duty;
				if (tmpdelta > 0)
				{
					*ptr += (rand() % (tmpdelta * 2)) - tmpdelta;
				}
			}
			else if (g_all_data[n - 1][u].data_type == BINARY)
			{
				// Pointeur vers l'emplacement mémoire où stocker les données BINARY dans le buffer circulaire
				uint8_t *ptr = (uint8_t *)((uint64_t)&buffer->data[buffer_index] + g_all_data[n - 1][u].offset);
				// Copie des données BINARY dans le buffer
				uint8_t data = (uint8_t)(g_all_data[n][u].binary);
				memcpy(ptr, &data, sizeof(uint8_t));
			}
		}
		// Enregistrement du timestamp dans le buffer circulaire
		buffer->data[buffer_index].timestamp = time(NULL);

		semop(semid, &P, 1); // Verrouiller le sémaphore

		// Copie du contenu du buffer circulaire dans la mémoire partagée
		shmp->cnt = sizeof(t_circular_buffer);
		memcpy(shmp->buf, buffer, sizeof(t_circular_buffer));
		shmp->complete = 0;
		semop(semid, &V, 1); // Déverrouiller le sémaphore

		printf("Sample n %d/%d acquired\n", i + 1, SAMPLES_NU);
		// Pause pour attendre le prochain 'fake' échantillon
		sleep(SAMPLE_RATE);
	}	
	
	// Marquage de la fin de la génération des échantillons
	shmp->complete = 1;

	// Détachement de la mémoire partagée
	if (shmdt(shmp) == -1)
	{
		perror("shmdt");
		return 1;
	}

	// Suppression de la mémoire partagée
	if (shmctl(shmid, IPC_RMID, 0) == -1)
	{
		perror("shmctl");
		return 1;
	}

	printf("Writing Process: Complete\n");

	sleep(1);
	kill(g_pid, SIGTERM);
	sleep(1);
	kill(g_pid, SIGSTOP);
	kill(g_pid, SIGINT);
}
