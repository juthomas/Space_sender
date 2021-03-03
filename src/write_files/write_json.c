#include "../../inc/sender.h"


void	write_json(t_data_info	*data)
{
	for (int i = 0; i < SAMPLES_NU; i++)
	{
		printf("{\n");
		for (int u = 0; u < DATAS_SIZE; u++)
		{
			printf("	%s : %f\n",data[i].datas[u].name, data[i].datas[u].float_data);
			// data[i].datas[u] = g_datas[u];
		}
		printf("}\n");
	}
}
