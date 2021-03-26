#include "../inc/sender.h"
#include <signal.h>

void	usage()
{
	printf("Usage : ");
	printf("data_sender \"Path/To/Destination/Folder\"\n");
}

int		main(int argc, char **argv)
{
	t_data_info *data;
	time_t now;
	struct tm tm_now;

	pid_t pid = fork();
	printf("PID : %d\n", pid);

	if (pid == 0)
	{
		printf("Hola !\n");

		execl("../midiWritingInC/midi_controller", "../midiWritingInC/midi_controller");

		exit(1);
	}

	// kill(pid, SIGKILL);SIGSTOP

	//Memory Allocation
	data = (t_data_info *)malloc(sizeof(t_data_info) * SAMPLES_NU);
	for (int i = 0; i < SAMPLES_NU; i++)
	{
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
				data[i].datas[u].float_data += fmod((float)rand() / 13., data[i].datas[u].float_delta) - (data[i].datas[u].float_delta / 2);
			}
			now = time(NULL);
			tm_now = *localtime(&now);
			char s_now[sizeof("AAAA/MM/JJ HH:MM:SS")];
			strftime(s_now, sizeof(s_now), "%Y/%m/%d %H:%M:%S", &tm_now);
			data[i].time = strdup(s_now);

			// printf("Time : %s\n", s_now);
			printf("Sample n°%d/%d acquired\n", i + 1, SAMPLES_NU);
			sleep(SAMPLE_RATE);
		}

		//Files Saving
		char s_filename[sizeof("AAAA_MM_JJ__HH_MM_SS.json")];
		strftime(s_filename, sizeof(s_filename), "%Y_%m_%d__%H_%M_%S.json", &tm_now);
		if (argc > 1)
		{
			char s_filepath[sizeof(s_filename) + strlen(argv[1]) + 1];
			sprintf(s_filepath, "%s/%s", argv[1], s_filename);
			write_json(data, s_filepath);
		}
		else
		{
			write_json(data, s_filename);
		}
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
	kill(pid, SIGTERM);
	sleep(1);
	kill(pid, SIGSTOP);
}