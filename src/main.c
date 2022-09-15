#include "../inc/sender.h"

void usage()
{
	printf("Usage : ");
	printf("data_sender \"Path/To/Destination/Folder\" \"Parg/To/Midi/Folder\"\n");
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
	time_t now;
	char *data_file_path; // = "../Space_MIDI/data_files";
	char *midi_file_path;

	if (argc == 3)
	{
		data_file_path = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 2));
		sprintf(data_file_path, "%s/", argv[1]);
		midi_file_path = (char *)malloc(sizeof(char) * (strlen(argv[2]) + 2));
		sprintf(midi_file_path, "%s/", argv[2]);
	}
	else
	{
		data_file_path = (char *)malloc(sizeof(char) * (sizeof("./Space_MIDI/data_files/") + 1));
		data_file_path = strcpy(data_file_path, "./Space_MIDI/data_files/");

		midi_file_path = (char *)malloc(sizeof(char) * (sizeof("./Space_MIDI/midi_files/") + 1));
		midi_file_path = strcpy(midi_file_path, "./Space_MIDI/midi_files/");
	}

	g_pid = fork();
	printf("PID : %d\n", g_pid);
	make_path(data_file_path, 0755);

	if (g_pid == 0)
	{
		/**
		 * Default path :
		 * execl("../Space_MIDI/midi_controller", "midi_controller",\
		 *  "../Space_MIDI/data_files", "../Space_MIDI/midi_files", NULL);
		 */

		execl("./Space_MIDI/midi_controller", "midi_controller",
			  data_file_path, midi_file_path, NULL);

		exit(1);
	}

	signal(SIGINT, (void (*)(int))close_child);

	t_circular_buffer *buffer;

	buffer = (t_circular_buffer *)malloc(sizeof(t_circular_buffer));

	int shmid;
	struct shmseg *shmp;
	char *bufptr;
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

	bufptr = shmp->buf;

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
				float *ptr = (float *)((uint64_t)&buffer->data[buffer_index] + g_all_data[n - 1][u].offset);

				*ptr = g_all_data[n - 1][u].float_data * (1 - duty) + g_all_data[n][u].float_data * duty;
				float tmpdelta = g_all_data[n - 1][u].float_delta * (1 - duty) + g_all_data[n][u].float_delta * duty;
				if (tmpdelta > 0)
				{
					*ptr += fmod((float)rand() / 13., tmpdelta * 2) - (tmpdelta);
				}
			}
			else if (g_all_data[n - 1][u].data_type == INTEGER)
			{
				uint32_t *ptr = (uint32_t *)((uint64_t)&buffer->data[buffer_index] + g_all_data[n - 1][u].offset);
				*ptr = (float)g_all_data[n - 1][u].int_data * (1 - duty) + g_all_data[n][u].int_data * duty;
				int tmpdelta = (float)g_all_data[n - 1][u].int_delta * (1 - duty) + g_all_data[n][u].int_delta * duty;
				if (tmpdelta > 0)
				{
					*ptr += (rand() % (tmpdelta * 2)) - tmpdelta;
				}
			}
			else if (g_all_data[n - 1][u].data_type == BINARY)
			{
				uint8_t *ptr = (uint8_t *)((uint64_t)&buffer->data[buffer_index] + g_all_data[n - 1][u].offset);
				*ptr = g_all_data[n][u].binary;
			}
		}
		now = time(NULL);

		buffer->data[buffer_index].timestamp = time(NULL);

		shmp->cnt = sizeof(t_circular_buffer);
		memcpy(shmp->buf, buffer, sizeof(t_circular_buffer));
		shmp->complete = 0;

		printf("Sample n°%d/%d acquired\n", i + 1, SAMPLES_NU);
		sleep(SAMPLE_RATE);
	}
	shmp->complete = 1;

	if (shmdt(shmp) == -1)
	{
		perror("shmdt");
		return 1;
	}

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
