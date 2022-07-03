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
	printf("Killing child\n");
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
	// printf("%lu, %lu\n", sizeof(g_all_data), sizeof(t_data*));
	// printf("%f", g_all_data[1][15].float_delta);
	// return(0);

	if (argc == 3)
	{
		data_file_path = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 2));
		sprintf(data_file_path, "%s/", argv[1]);
		midi_file_path = (char*)malloc(sizeof(char) * (strlen(argv[2]) + 2));
		sprintf(midi_file_path, "%s/", argv[2]);
	}
	else
	{
		data_file_path = (char*)malloc(sizeof(char) * (sizeof("../Space_MIDI/data_files/") + 1));
		data_file_path = strcpy(data_file_path, "../Space_MIDI/data_files/");
		
		midi_file_path = (char*)malloc(sizeof(char) * (sizeof("../Space_MIDI/midi_files/") + 1));
		midi_file_path = strcpy(midi_file_path, "../Space_MIDI/midi_files/");
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
	
		execl("../Space_MIDI/midi_controller", "midi_controller",\
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


	int max_steps = FILES_NU * SAMPLES_NU; // 20
	int current_step = 0;

	int number_of_data_steps = (sizeof(g_all_data) / sizeof(t_data*)) - 1 ;

	int current_data_step_min = 0;
	int current_data_step_max = 0;



	//Writing Eatch File
	for (int current_file = 0; current_file < FILES_NU; current_file++)
	{

		//Data Feeding
		for (int i = 0; i < SAMPLES_NU; i++, current_step++)
		{
			int n = 1;
			while (!(((max_steps / number_of_data_steps) * (n - 1) <= current_step)
			&& ((max_steps / number_of_data_steps) * (n) > current_step)))
			{
				// printf("In the while, %d\n", n);
				// printf("n-1 gloal : %d\n", (max_steps / number_of_data_steps) * (n - 1));
				// printf("n gloal : %d\n", (max_steps / number_of_data_steps) * (n));
				// printf("current step : %d\n", current_step);
				n++;
			}
			float duty;
			current_data_step_min = (max_steps / number_of_data_steps) * (n - 1);
			current_data_step_max = (max_steps / number_of_data_steps) * (n);

			duty = ((float)current_step - current_data_step_min) / (current_data_step_max - current_data_step_min);
			printf("N : %d, duty : %f\n",n, duty);
			printf("step min : %d\n",current_data_step_min);
			printf("step max : %d\n",current_data_step_max);
			printf("current step : %d/%d\n\n", current_step, SAMPLES_NU * FILES_NU);


			for (int u = 0; u < DATAS_SIZE; u++)
			{
				// data[i].datas[u] = g_datas[u];
				data[i].datas[u] = g_all_data[n - 1][u];


				if (data[i].datas[u].data_type == FLOATING)
				{
					data[i].datas[u].float_data = g_all_data[n - 1][u].float_data * (1-duty) + g_all_data[n][u].float_data * duty;
					float tmpdelta = g_all_data[n - 1][u].float_delta * (1-duty) + g_all_data[n][u].float_delta * duty;
					if (tmpdelta > 0)
					{
						data[i].datas[u].float_data += fmod((float)rand() / 13., tmpdelta * 2) - (tmpdelta);
					}
					// if (u == 0)
					// {
					// 	printf("%s : %f\n", data[i].datas[u].name,data[i].datas[u].float_data);
					// 	// printf("tmpdelta : ")
					// }
				}
				else if (data[i].datas[u].data_type == INTEGER)
				{
					data[i].datas[u].int_data = (float)g_all_data[n - 1][u].int_data * (1-duty) + g_all_data[n][u].int_data * duty;
					int tmpdelta = (float)g_all_data[n - 1][u].int_delta * (1-duty) + g_all_data[n][u].int_delta * duty;
					if (tmpdelta > 0)
					{
						data[i].datas[u].int_data += (rand() % (tmpdelta * 2)) - tmpdelta;
					}
				}
				else if (data[i].datas[u].data_type == BINARY)
				{
					// data[i].datas[u].binary += rand() % 2;
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
	sleep(1);
	kill(g_pid, SIGTERM);
	sleep(1);
	kill(g_pid, SIGSTOP);
	kill(g_pid, SIGINT);

}
