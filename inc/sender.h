#ifndef SENDER_H
# define SENDER_H
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# define SAMPLES_NU 10
# define SAMPLE_RATE 1 //RATE LOOP IN SECONDS
# define FILES_NU 3

enum			e_data_type
{
	INTEGER = 0,
	FLOATING
};

typedef struct	s_data
{
	char		*name;
	uint8_t		data_type;
	uint32_t	int_data;
	float		float_data;
	uint32_t	int_delta;
	float		float_delta;
}				t_data;

#define DATAS_SIZE 5

static const t_data	g_datas[DATAS_SIZE] = {
(t_data){.name = "Photodiode", .data_type = FLOATING, .float_data = 42, .float_delta = 4},
(t_data){.name = "Temperature", .data_type = FLOATING, .float_data = 42, .float_delta = 4},
(t_data){.name = "Consumption", .data_type = FLOATING, .float_data = 42, .float_delta = 4},
(t_data){.name = "Position", .data_type = FLOATING, .float_data = 42, .float_delta = 4},
(t_data){.name = "Orgue", .data_type = FLOATING, .float_data = 42, .float_delta = 4},
};

typedef struct	s_data_info
{
	t_data		*datas;
	char		*time;
}				t_data_info;

void	write_json(t_data_info	*data, char *filename);

#endif