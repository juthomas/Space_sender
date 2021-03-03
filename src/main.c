#include "../inc/sender.h"

int main()
{
	t_data_info	*data;

	data = (t_data_info*)malloc(sizeof(t_data_info) * SAMPLES_NU);
	for (int i = 0; i < SAMPLES_NU; i++)
	{
		data[i].datas = (t_data*)malloc(sizeof(t_data) * DATAS_SIZE);
		for (int u = 0; u < DATAS_SIZE; u++)
		{
			data[i].datas[u] = g_datas[u];
			data[i].datas[u].float_data += fmod((float)rand()/13., data[i].datas[u].float_delta) - (data[i].datas[u].float_delta / 2);
		}
	}

	write_json(data);


	printf("Hello World !\n");
}