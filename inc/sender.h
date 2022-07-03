#ifndef SENDER_H
# define SENDER_H
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# define SAMPLES_NU 10 //NUMBER OF SAMPLES IN FILES
# define SAMPLE_RATE 1 //RATE LOOP IN SECONDS
# define FILES_NU 30 //NUMBER OF FILES

pid_t g_pid;
int errno;

enum			e_data_type
{
	INTEGER = 0,
	FLOATING,
	BINARY
};

typedef struct	s_data
{
	char		*name;
	uint8_t		data_type;
	uint32_t	int_data;
	float		float_data;
	uint32_t	int_delta;
	float		float_delta;
	uint8_t		binary;
}				t_data;

#define DATAS_SIZE 33

static const t_data	g_datas[] = {
(t_data){.name = "Photodiode_1", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Photodiode_2", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Photodiode_3", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Photodiode_4", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Photodiode_5", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Photodiode_6", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_1", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_2", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_3", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_4", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_5", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_6", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_7", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_8", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_9", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "Temperature_10", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
(t_data){.name = "First_sample", .data_type = BINARY, .binary = 0},
(t_data){.name = "Spectro_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
(t_data){.name = "Organ_current", .data_type = FLOATING, .float_data = 0.05, .float_delta = 0.05},
(t_data){.name = "Vin_current", .data_type = FLOATING, .float_data = 1.25, .float_delta = 0.75},
(t_data){.name = "Q7_current", .data_type = FLOATING, .float_data = 0.1, .float_delta = 0.1},
(t_data){.name = "5v_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
(t_data){.name = "3.3v_current", .data_type = FLOATING, .float_data = 0.25, .float_delta = 0.25},
(t_data){.name = "Motor_current", .data_type = FLOATING, .float_data = 0.025, .float_delta = 0.025},
(t_data){.name = "Carousel_state", .data_type = INTEGER, .int_data = 80, .int_delta = 80},
(t_data){.name = "Lid_state", .data_type = INTEGER, .int_data = 36, .int_delta = 36},
(t_data){.name = "Spectrum", .data_type = INTEGER, .int_data = 10000, .int_delta = 10000},
(t_data){.name = "Organ_1", .data_type = INTEGER, .int_data = 512, .int_delta = 512},
(t_data){.name = "Organ_2", .data_type = INTEGER, .int_data = 512, .int_delta = 512},
(t_data){.name = "Organ_3", .data_type = INTEGER, .int_data = 512, .int_delta = 512},
(t_data){.name = "Organ_4", .data_type = INTEGER, .int_data = 512, .int_delta = 512},
(t_data){.name = "Organ_5", .data_type = INTEGER, .int_data = 512, .int_delta = 512},
(t_data){.name = "Organ_6", .data_type = INTEGER, .int_data = 512, .int_delta = 512}
};


// Donnees en passant par des etapes
static const t_data *g_all_data[] = {
	(t_data[]){
		(t_data){.name = "Photodiode_1", .data_type = INTEGER, .int_data = 20, .int_delta = 20},
		(t_data){.name = "Photodiode_2", .data_type = INTEGER, .int_data = 20, .int_delta = 20},
		(t_data){.name = "Photodiode_3", .data_type = INTEGER, .int_data = 20, .int_delta = 20},
		(t_data){.name = "Photodiode_4", .data_type = INTEGER, .int_data = 20, .int_delta = 20},
		(t_data){.name = "Photodiode_5", .data_type = INTEGER, .int_data = 20, .int_delta = 20},
		(t_data){.name = "Photodiode_6", .data_type = INTEGER, .int_data = 20, .int_delta = 20},
		(t_data){.name = "Temperature_1", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_2", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_3", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_4", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_5", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_6", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_7", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_8", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_9", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_10", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "First_sample", .data_type = BINARY, .binary = 0},
		(t_data){.name = "Spectro_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
		(t_data){.name = "Organ_current", .data_type = FLOATING, .float_data = 0.05, .float_delta = 0.05},
		(t_data){.name = "Vin_current", .data_type = FLOATING, .float_data = 1.25, .float_delta = 0.75},
		(t_data){.name = "Q7_current", .data_type = FLOATING, .float_data = 0.1, .float_delta = 0.1},
		(t_data){.name = "5v_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
		(t_data){.name = "3.3v_current", .data_type = FLOATING, .float_data = 0.25, .float_delta = 0.25},
		(t_data){.name = "Motor_current", .data_type = FLOATING, .float_data = 0.025, .float_delta = 0.025},
		(t_data){.name = "Carousel_state", .data_type = INTEGER, .int_data = 0, .int_delta = 0},
		(t_data){.name = "Lid_state", .data_type = INTEGER, .int_data = 36, .int_delta = 36},
		(t_data){.name = "Spectrum", .data_type = INTEGER, .int_data = 5000, .int_delta = 0},
		(t_data){.name = "Organ_1", .data_type = INTEGER, .int_data = 10, .int_delta = 2},
		(t_data){.name = "Organ_2", .data_type = INTEGER, .int_data = 10, .int_delta = 2},
		(t_data){.name = "Organ_3", .data_type = INTEGER, .int_data = 10, .int_delta = 2},
		(t_data){.name = "Organ_4", .data_type = INTEGER, .int_data = 10, .int_delta = 2},
		(t_data){.name = "Organ_5", .data_type = INTEGER, .int_data = 10, .int_delta = 2},
		(t_data){.name = "Organ_6", .data_type = INTEGER, .int_data = 10, .int_delta = 2}
	},
		(t_data[]){
		(t_data){.name = "Photodiode_1", .data_type = INTEGER, .int_data = 2048, .int_delta = 20},
		(t_data){.name = "Photodiode_2", .data_type = INTEGER, .int_data = 2048, .int_delta = 20},
		(t_data){.name = "Photodiode_3", .data_type = INTEGER, .int_data = 2048, .int_delta = 20},
		(t_data){.name = "Photodiode_4", .data_type = INTEGER, .int_data = 2048, .int_delta = 20},
		(t_data){.name = "Photodiode_5", .data_type = INTEGER, .int_data = 2048, .int_delta = 20},
		(t_data){.name = "Photodiode_6", .data_type = INTEGER, .int_data = 2048, .int_delta = 20},
		(t_data){.name = "Temperature_1", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_2", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_3", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_4", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_5", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_6", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_7", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_8", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_9", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_10", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "First_sample", .data_type = BINARY, .binary = 0},
		(t_data){.name = "Spectro_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
		(t_data){.name = "Organ_current", .data_type = FLOATING, .float_data = 0.05, .float_delta = 0.05},
		(t_data){.name = "Vin_current", .data_type = FLOATING, .float_data = 1.25, .float_delta = 0.75},
		(t_data){.name = "Q7_current", .data_type = FLOATING, .float_data = 0.1, .float_delta = 0.1},
		(t_data){.name = "5v_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
		(t_data){.name = "3.3v_current", .data_type = FLOATING, .float_data = 0.25, .float_delta = 0.25},
		(t_data){.name = "Motor_current", .data_type = FLOATING, .float_data = 0.025, .float_delta = 0.025},
		(t_data){.name = "Carousel_state", .data_type = INTEGER, .int_data = 60, .int_delta = 0},
		(t_data){.name = "Lid_state", .data_type = INTEGER, .int_data = 36, .int_delta = 36},
		(t_data){.name = "Spectrum", .data_type = INTEGER, .int_data = 5000, .int_delta = 0},
		(t_data){.name = "Organ_1", .data_type = INTEGER, .int_data = 50, .int_delta = 2},
		(t_data){.name = "Organ_2", .data_type = INTEGER, .int_data = 50, .int_delta = 2},
		(t_data){.name = "Organ_3", .data_type = INTEGER, .int_data = 50, .int_delta = 2},
		(t_data){.name = "Organ_4", .data_type = INTEGER, .int_data = 50, .int_delta = 2},
		(t_data){.name = "Organ_5", .data_type = INTEGER, .int_data = 50, .int_delta = 2},
		(t_data){.name = "Organ_6", .data_type = INTEGER, .int_data = 50, .int_delta = 2}
	},
		(t_data[]){
		(t_data){.name = "Photodiode_1", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_2", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_3", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_4", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_5", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_6", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Temperature_1", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_2", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_3", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_4", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_5", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_6", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_7", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_8", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_9", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_10", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "First_sample", .data_type = BINARY, .binary = 0},
		(t_data){.name = "Spectro_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
		(t_data){.name = "Organ_current", .data_type = FLOATING, .float_data = 0.05, .float_delta = 0.05},
		(t_data){.name = "Vin_current", .data_type = FLOATING, .float_data = 1.25, .float_delta = 0.75},
		(t_data){.name = "Q7_current", .data_type = FLOATING, .float_data = 0.1, .float_delta = 0.1},
		(t_data){.name = "5v_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
		(t_data){.name = "3.3v_current", .data_type = FLOATING, .float_data = 0.25, .float_delta = 0.25},
		(t_data){.name = "Motor_current", .data_type = FLOATING, .float_data = 0.025, .float_delta = 0.025},
		(t_data){.name = "Carousel_state", .data_type = INTEGER, .int_data = 120, .int_delta = 0},
		(t_data){.name = "Lid_state", .data_type = INTEGER, .int_data = 36, .int_delta = 36},
		(t_data){.name = "Spectrum", .data_type = INTEGER, .int_data = 15000, .int_delta = 0},
		(t_data){.name = "Organ_1", .data_type = INTEGER, .int_data = 512, .int_delta = 2},
		(t_data){.name = "Organ_2", .data_type = INTEGER, .int_data = 512, .int_delta = 2},
		(t_data){.name = "Organ_3", .data_type = INTEGER, .int_data = 512, .int_delta = 2},
		(t_data){.name = "Organ_4", .data_type = INTEGER, .int_data = 512, .int_delta = 2},
		(t_data){.name = "Organ_5", .data_type = INTEGER, .int_data = 512, .int_delta = 2},
		(t_data){.name = "Organ_6", .data_type = INTEGER, .int_data = 512, .int_delta = 2}
	},
		(t_data[]){
		(t_data){.name = "Photodiode_1", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_2", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_3", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_4", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_5", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Photodiode_6", .data_type = INTEGER, .int_data = 4040, .int_delta = 20},
		(t_data){.name = "Temperature_1", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_2", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_3", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_4", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_5", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_6", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_7", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_8", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_9", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "Temperature_10", .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
		(t_data){.name = "First_sample", .data_type = BINARY, .binary = 0},
		(t_data){.name = "Spectro_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
		(t_data){.name = "Organ_current", .data_type = FLOATING, .float_data = 0.05, .float_delta = 0.05},
		(t_data){.name = "Vin_current", .data_type = FLOATING, .float_data = 1.25, .float_delta = 0.75},
		(t_data){.name = "Q7_current", .data_type = FLOATING, .float_data = 0.1, .float_delta = 0.1},
		(t_data){.name = "5v_current", .data_type = FLOATING, .float_data = 0.5, .float_delta = 0.5},
		(t_data){.name = "3.3v_current", .data_type = FLOATING, .float_data = 0.25, .float_delta = 0.25},
		(t_data){.name = "Motor_current", .data_type = FLOATING, .float_data = 0.025, .float_delta = 0.025},
		(t_data){.name = "Carousel_state", .data_type = INTEGER, .int_data = 179, .int_delta = 0},
		(t_data){.name = "Lid_state", .data_type = INTEGER, .int_data = 36, .int_delta = 36},
		(t_data){.name = "Spectrum", .data_type = INTEGER, .int_data = 15000, .int_delta = 0},
		(t_data){.name = "Organ_1", .data_type = INTEGER, .int_data = 1000, .int_delta = 2},
		(t_data){.name = "Organ_2", .data_type = INTEGER, .int_data = 1000, .int_delta = 2},
		(t_data){.name = "Organ_3", .data_type = INTEGER, .int_data = 1000, .int_delta = 2},
		(t_data){.name = "Organ_4", .data_type = INTEGER, .int_data = 1000, .int_delta = 2},
		(t_data){.name = "Organ_5", .data_type = INTEGER, .int_data = 1000, .int_delta = 2},
		(t_data){.name = "Organ_6", .data_type = INTEGER, .int_data = 1000, .int_delta = 2}
	}
};

typedef struct	s_data_info
{
	t_data		*datas;
	char		*time;
}				t_data_info;

void	write_json(t_data_info	*data, char *filename);

#endif
