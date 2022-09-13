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
	// t_data_info *data;
	time_t now;
	struct tm tm_now;
	char *data_file_path; // = "../Space_MIDI/data_files";
	char *midi_file_path;
	// printf("%lu, %lu\n", sizeof(g_all_data), sizeof(t_data*));
	// printf("%f", g_all_data[1][15].float_delta);
	// return(0);

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

	// kill(pid, SIGKILL);SIGSTOP
	signal(SIGINT, (void (*)(int))close_child);

	t_circular_buffer *buffer;

	buffer = (t_circular_buffer*)malloc(sizeof(t_circular_buffer));

	// Memory Allocation
	//  data = (t_data_info *)malloc(sizeof(t_data_info) * SAMPLES_NU);
	//  for (int i = 0; i < SAMPLES_NU; i++)
	//  {
	//  	data[i].time = (char*)malloc(sizeof("AAAA/mm/JJ HH:MM:SS"));
	//  	data[i].datas = (t_data *)malloc(sizeof(t_data) * DATAS_SIZE);
	//  }

	int shmid, numtimes;
	struct shmseg *shmp;
	char *bufptr;
	//    int spaceavailable;
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

	// Writing Eatch File
	//  for (int current_file = 0; current_file < FILES_NU; current_file++)
	//  {

	// Data Feeding
	// shmp->cnt = sizeof(t_circular_buffer);
	// buffer = (t_circular_buffer *)shmp->buf;
	bzero(buffer, sizeof(t_circular_buffer));
	for (int i = 0; i < SAMPLES_NU; i++, current_step++)
	{

		// buffer = (t_circular_buffer *)shmp->buf;

	// bzero(buffer, sizeof(t_circular_buffer));
	// buffer->buffer_rounds = 42;
	buffer->older_block = 43;


		// shmp->cnt = sizeof(t_circular_buffer);
		// buffer = (t_circular_buffer *)shmp->buf;
		// bzero(buffer, sizeof(t_circular_buffer));

		buffer_index = i % 10;
		int n = 1;
		// while (!(((max_steps / number_of_data_steps) * (n - 1) <= current_step) && ((max_steps / number_of_data_steps) * (n) > current_step)))
		// {
		// 	// printf("In the while, %d\n", n);
		// 	// printf("n-1 gloal : %d\n", (max_steps / number_of_data_steps) * (n - 1));
		// 	// printf("n gloal : %d\n", (max_steps / number_of_data_steps) * (n));
		// 	// printf("current step : %d\n", current_step);
		// 	n++;
		// }
		n = ((number_of_data_steps ) * current_step / max_steps) + 1;
		float duty;
		current_data_step_min = (max_steps / number_of_data_steps) * (n - 1);
		current_data_step_max = (max_steps / number_of_data_steps) * (n);

		duty = ((float)current_step - current_data_step_min) / (current_data_step_max - current_data_step_min);
		// printf("N : %d, duty : %f\n", n, duty);
		// printf("step min : %d\n", current_data_step_min);
		// printf("step max : %d\n", current_data_step_max);
		// printf("current step : %d/%d\n\n", current_step, SAMPLES_NU);

		for (int u = 0; u < DATAS_SIZE; u++)
		{
			// data[i].datas[u] = g_datas[u];
			// data[i].datas[u] = g_all_data[n - 1][u];

			// printf("N : %d, U : %d\n", n, u);
			if (g_all_data[n - 1][u].data_type == FLOATING)
			{
				float *ptr = (float *)((uint64_t)&buffer->data[buffer_index] + g_all_data[n - 1][u].offset);

				*ptr = g_all_data[n - 1][u].float_data * (1 - duty) + g_all_data[n][u].float_data * duty;
				float tmpdelta = g_all_data[n - 1][u].float_delta * (1 - duty) + g_all_data[n][u].float_delta * duty;
				if (tmpdelta > 0)
				{
					*ptr += fmod((float)rand() / 13., tmpdelta * 2) - (tmpdelta);
				}
				// if (u == 0)
				// {
				// 	printf("%s : %f\n", data[i].datas[u].name,data[i].datas[u].float_data);
				// 	// printf("tmpdelta : ")
				// }
			}
			else if (g_all_data[n - 1][u].data_type == INTEGER)
			{
				uint32_t *ptr = (uint32_t *)((uint64_t)&buffer->data[buffer_index] + g_all_data[n - 1][u].offset);
				// printf("Index n => %d, index u => %d\n", n, u);
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
		// printf("ORIGINAL TIMESTAMP [%d] : %llu\n",buffer_index, buffer->data[buffer_index].timestamp);
		
		// printf("SENDER FIRST TIMESTAMP OFFSET %d\n", ((long)&buffer->data[0].timestamp - (long)buffer));


		shmp->cnt = sizeof(t_circular_buffer);
		memcpy(shmp->buf, buffer, sizeof(t_circular_buffer));
		shmp->complete = 0;
		// bufptr = shmp->buf;

		// tm_now = *localtime(&buffer->data[buffer_index].timestamp);//
		// char s_now[sizeof("AAAA/mm/JJ HH:MM:SS")];

		// strftime(data[i].time, sizeof("AAAA/mm/JJ HH:MM:SS"), "%Y/%m/%d %H:%M:%S", &tm_now);//
		// data[i].time = strdup(s_now);

		// printf("Time : %s\n", s_now);
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

	// Files Saving
	// 	char s_filename[sizeof("AAAA_mm_JJ__HH_MM_SS.json")];
	// 	strftime(s_filename, sizeof(s_filename), "%Y_%m_%d__%H_%M_%S.json", &tm_now);
	// 	// if (argc > 1)
	// 	// {
	// 		char s_filepath[sizeof(s_filename) + strlen(data_file_path)];
	// 		sprintf(s_filepath, "%s%s", data_file_path, s_filename);
	// 		write_json(data, s_filepath);
	// 	// }
	// 	// else
	// 	// {
	// 	// 	write_json(data, s_filename);
	// 	// }
	// 	printf("File n°%d/%d writed\n", current_file + 1, FILES_NU);
	// }

	// Freeing Memory
	//  for (int i = 0; i < SAMPLES_NU; i++)
	//  {
	//  	free(data[i].time);
	//  	free(data[i].datas);
	//  }
	//  free(data);
	sleep(1);
	kill(g_pid, SIGTERM);
	sleep(1);
	kill(g_pid, SIGSTOP);
	kill(g_pid, SIGINT);
}
