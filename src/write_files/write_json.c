#include "../../inc/sender.h"


void	write_json(t_data_info	*data, char *filename)
{
	FILE *file_ptr;
	if (!(file_ptr = fopen(filename, "w")) )
	{
		printf("Error while creating file :%s\n", filename);
		exit(-1);
	}
	fprintf(file_ptr, "\"Datas\" : [\n");
	for (int i = 0; i < SAMPLES_NU; i++)
	{
		fprintf(file_ptr, "	{\n");
		fprintf(file_ptr, "		\"Time\" : \"%s\",\n", data[i].time);
		for (int u = 0; u < DATAS_SIZE; u++)
		{
			fprintf(file_ptr, "		\"%s\" : %f,\n",data[i].datas[u].name, data[i].datas[u].float_data);
		}
		fprintf(file_ptr, "	},\n");
	}
	fprintf(file_ptr, "]\n");
	fclose(file_ptr);
}
