#include "../inc/sender.h"

void	usage()
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
int make_path(char* file_path, mode_t mode) {
	for (char* p = strchr(file_path + 1, '/'); p; p = strchr(p + 1, '/')) {
		*p = '\0';
		if (mkdir(file_path, mode) == -1) {
			if (errno != EEXIST) {
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
	(void)signal;
	kill(g_pid, SIGINT);
	exit(0);
}


/**
 * argv[1] = data_files_path
 * argv[2] = midi_files_path
*/
int		main(int argc, char **argv)
{
	t_data_info *data;
	time_t now;
	struct tm tm_now;
	char *data_file_path;// = "../Space_MIDI/data_files";
	char *midi_file_path;

	if (argc == 3)
	{
		data_file_path = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 2));
		sprintf(data_file_path, "%s/", argv[1]);
		midi_file_path = (char*)malloc(sizeof(char) * (strlen(argv[2]) + 2));
		sprintf(midi_file_path, "%s/", argv[2]);
	}
	else
	{
		data_file_path = (char*)malloc(sizeof(char) * (sizeof("./Space_MIDI/data_files/") + 1));
		data_file_path = strcpy(data_file_path, "./Space_MIDI/data_files/");
		
		midi_file_path = (char*)malloc(sizeof(char) * (sizeof("./Space_MIDI/midi_files/") + 1));
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
	
		execl("./Space_MIDI/midi_controller", "midi_controller",\
		 data_file_path, midi_file_path, NULL);

		exit(1);
	}

	// kill(pid, SIGKILL);SIGSTOP
	signal(SIGINT, (void (*)(int))close_child);

	//Memory Allocation
	data = (t_data_info *)malloc(sizeof(t_data_info) * SAMPLES_NU);
	for (int i = 0; i < SAMPLES_NU; i++)
	{
		data[i].time = (char*)malloc(sizeof("AAAA/mm/JJ HH:MM:SS"));
		data[i].datas = (t_data *)malloc(sizeof(t_data) * DATAS_SIZE);
	}

	//Writing Eatch File
	for (int current_file = 0; current_file < FILES_NU; current_file++)
	{

		//Data Feeding
		for (int i = 0; i < SAMPLES_NU; i++)
		{
			for (int u = 0; u < DATAS_SIZE; u++)
			{
				data[i].datas[u] = g_datas[u];
				if (data[i].datas[u].data_type == FLOATING)
				{
					data[i].datas[u].float_data += fmod((float)rand() / 13., data[i].datas[u].float_delta * 2) - (data[i].datas[u].float_delta);
				}
				else if (data[i].datas[u].data_type == INTEGER)
				{
					data[i].datas[u].int_data += (rand() % data[i].datas[u].int_delta * 2) - data[i].datas[u].int_delta;
				}
				else if (data[i].datas[u].data_type == BINARY)
				{
					data[i].datas[u].binary += rand() % 2;
				}
			}
			now = time(NULL);
			tm_now = *localtime(&now);
			// char s_now[sizeof("AAAA/mm/JJ HH:MM:SS")];
			strftime(data[i].time, sizeof("AAAA/mm/JJ HH:MM:SS"), "%Y/%m/%d %H:%M:%S", &tm_now);
			// data[i].time = strdup(s_now);

			// printf("Time : %s\n", s_now);
			printf("Sample n°%d/%d acquired\n", i + 1, SAMPLES_NU);
			sleep(SAMPLE_RATE);
		}

		//Files Saving
		char s_filename[sizeof("AAAA_mm_JJ__HH_MM_SS.json")];
		strftime(s_filename, sizeof(s_filename), "%Y_%m_%d__%H_%M_%S.json", &tm_now);
		// if (argc > 1)
		// {
			char s_filepath[sizeof(s_filename) + strlen(data_file_path)];
			sprintf(s_filepath, "%s%s", data_file_path, s_filename);
			write_json(data, s_filepath);
		// }
		// else
		// {
		// 	write_json(data, s_filename);
		// }
		printf("File n°%d/%d writed\n", current_file + 1, FILES_NU);
	}

	//Freeing Memory
	for (int i = 0; i < SAMPLES_NU; i++)
	{
		free(data[i].time);
		free(data[i].datas);
	}
	free(data);
	printf("End Of Program !\n");
		sleep(1);
	kill(g_pid, SIGTERM);
	sleep(1);
	kill(g_pid, SIGSTOP);
}
