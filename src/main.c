#include "../inc/sender.h"

int main(int argc, char **argv)
{
	t_data_info	*data;
	time_t now;
	struct tm tm_now;

	data = (t_data_info*)malloc(sizeof(t_data_info) * SAMPLES_NU);
	for (int i = 0; i < SAMPLES_NU; i++)
	{
		data[i].datas = (t_data*)malloc(sizeof(t_data) * DATAS_SIZE);
		for (int u = 0; u < DATAS_SIZE; u++)
		{
			data[i].datas[u] = g_datas[u];
			data[i].datas[u].float_data += fmod((float)rand()/13., data[i].datas[u].float_delta) - (data[i].datas[u].float_delta / 2);

		}
		now = time(NULL);
		tm_now = *localtime(&now);
		char s_now[sizeof("JJ/MM/AAAA HH:MM:SS")];
		strftime(s_now, sizeof(s_now), "%d/%m/%Y %H:%M:%S", &tm_now);
		data[i].time = s_now;
		printf("Sample n°%d/%d acquired\n", i + 1, SAMPLES_NU);
		sleep(SAMPLE_RATE);
	}


	char s_filename[sizeof("JJ_MM_AAAA__HH_MM_SS.json")];
	strftime(s_filename, sizeof(s_filename), "%d_%m_%Y__%H_%M_%S.json", &tm_now);


	write_json(data, s_filename);


	printf("Hello World !\n");
}