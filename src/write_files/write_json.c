#include "../../inc/sender.h"


void	write_json(t_data_info	*data, char *filename)
{
	FILE *file_ptr;
	if (!(file_ptr = fopen(filename, "w")) )
	{
		printf("Error while creating file :%s\n", filename);
		exit(-1);
	}
	fprintf(file_ptr, "{\n");
	fprintf(file_ptr, "\t\"Datas\" : [\n");
	for (int i = 0; i < SAMPLES_NU; i++)
	{
		fprintf(file_ptr, "\t\t{\n");
		fprintf(file_ptr, "\t\t\t\"Time\" : \"%s\",\n", data[i].time);
		for (int u = 0; u < DATAS_SIZE; u++)
		{
			if (data[i].datas[u].data_type == FLOATING)
			{
				fprintf(file_ptr, "\t\t\t\"%s\" : %f%s\n",data[i].datas[u].name,
				data[i].datas[u].float_data, u < DATAS_SIZE - 1 ? "," : "");
			}
			else if (data[i].datas[u].data_type == INTEGER)
			{
				fprintf(file_ptr, "\t\t\t\"%s\" : %d%s\n",data[i].datas[u].name,
				data[i].datas[u].int_data, u < DATAS_SIZE - 1 ? "," : "");
			}
			else if (data[i].datas[u].data_type == BINARY)
			{
				fprintf(file_ptr, "\t\t\t\"%s\" : %d%s\n",data[i].datas[u].name,
				data[i].datas[u].binary, u < DATAS_SIZE - 1 ? "," : "");
			}
		}
		fprintf(file_ptr, "\t\t}%s\n", i < SAMPLES_NU - 1 ? "," : "");
	}
	fprintf(file_ptr, "\t]\n");
	fprintf(file_ptr, "}\n");
	fclose(file_ptr);
}
