#ifndef SENDER_H
#define SENDER_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>

#include <stddef.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <sys/types.h>

//21h50
//1260 + 50 => 1310
//78 600 seconds => 7 860 Samples every 10 secs 
#define SAMPLES_NU 300 // NUMBER OF SAMPLES IN FILES
#define SAMPLE_RATE 10  // RATE LOOP IN SECONDS

#define SHM_KEY 0x1240 // Clé d'identification de la mémoire partagée
#define SEM_KEY 0x1240 // Clé d'identification des sémaphores

enum e_data_type
{
	INTEGER = 0,
	FLOATING,
	BINARY
};

typedef struct s_sensors
{
	uint16_t photodiode_1;	  // 0 - 4095
	uint16_t photodiode_2;	  // 0 - 4095
	uint16_t photodiode_3;	  // 0 - 4095
	uint16_t photodiode_4;	  // 0 - 4095
	uint16_t photodiode_5;	  // 0 - 4095
	uint16_t photodiode_6;	  // 0 - 4095
	uint16_t temperature_1;	  // 0 - 4095
	uint16_t temperature_2;	  // 0 - 4095
	uint16_t temperature_3;	  // 0 - 4095
	uint16_t temperature_4;	  // 0 - 4095
	uint16_t temperature_5;	  // 0 - 4095
	uint16_t temperature_6;	  // 0 - 4095
	uint16_t temperature_7;	  // 0 - 4095
	uint16_t temperature_8;	  // 0 - 4095
	uint16_t temperature_9;	  // 0 - 4095
	uint16_t temperature_10;  // 0 - 4095
	int8_t microphone;		  // 0 - 1
	uint16_t spectro_current; // 0 - 65535
	uint8_t organ_current;	  // 0 - 255
	uint16_t vin_current;	  // 0 - 65535//
	uint8_t q7_current;		  // 0 - 255
	uint8_t t5v_current;	  // 0 - 255
	uint8_t t3_3v_current;	  // 0 - 255
	uint16_t motor_current;	  // 0 - 65535
	uint8_t carousel_state;	  // 0 - 119
	uint8_t lid_state;		  // 0 - 53
	uint16_t organ_1;		  // 0 - 1023
	uint16_t organ_2;		  // 0 - 1023
	uint16_t organ_3;		  // 0 - 1023
	uint16_t organ_4;		  // 0 - 1023
	uint16_t organ_5;		  // 0 - 1023
	uint16_t organ_6;		  // 0 - 1023
	uint64_t timestamp;		  // 0 - oo
} t_sensors;

typedef struct s_data
{
	char *name;
	size_t offset;
	uint8_t data_type;
	uint32_t int_data;
	float float_data;
	uint32_t int_delta;
	float float_delta;
	uint8_t binary;
} t_data;

#define BUFFER_ROUNDS 42
typedef struct s_circular_buffer
{
	int16_t older_block;
	t_sensors data[BUFFER_ROUNDS];
} t_circular_buffer;

struct shmseg
{
	int cnt;
	int complete;
	char buf[sizeof(t_circular_buffer)];
};

#define DATAS_SIZE 32

//Date : 2023/10/10, Time : 16:54:52
static const t_data g_all_data_step_1[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1476, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1489, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1466, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 28706, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 16114, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 58, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 11717, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2639, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2976, .int_delta = 0}};

//Date : 2023/10/10, Time : 17:05:02
static const t_data g_all_data_step_2[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1485, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1510, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1471, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 53, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 4939, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 23, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 12254, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2326, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2468, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2974, .int_delta = 0}};

//Date : 2023/10/10, Time : 17:15:12
static const t_data g_all_data_step_3[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1491, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1504, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1478, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 4865, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 50, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 23, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 12381, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2639, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2974, .int_delta = 0}};

//Date : 2023/10/10, Time : 17:25:22
static const t_data g_all_data_step_4[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1496, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1503, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1483, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2527, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2467, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2974, .int_delta = 0}};

//Date : 2023/10/10, Time : 17:35:32
static const t_data g_all_data_step_5[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1497, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1501, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1486, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2326, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1653, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2640, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2976, .int_delta = 0}};

//Date : 2023/10/10, Time : 17:45:42
static const t_data g_all_data_step_6[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1497, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1488, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2533, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2468, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2973, .int_delta = 0}};

//Date : 2023/10/10, Time : 17:55:52
static const t_data g_all_data_step_7[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1498, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1488, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2661, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 44, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1518, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2326, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1653, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2640, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2975, .int_delta = 0}};

//Date : 2023/10/10, Time : 18:06:02
static const t_data g_all_data_step_8[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4016, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1496, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1489, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2654, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2975, .int_delta = 0}};

//Date : 2023/10/10, Time : 18:16:12
static const t_data g_all_data_step_9[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1497, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1489, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2696, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2467, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2639, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2974, .int_delta = 0}};

//Date : 2023/10/10, Time : 18:26:22
static const t_data g_all_data_step_10[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1498, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1490, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2471, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 43, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1518, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2973, .int_delta = 0}};

//Date : 2023/10/10, Time : 18:36:32
static const t_data g_all_data_step_11[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1498, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1490, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2675, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1653, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2639, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2974, .int_delta = 0}};

//Date : 2023/10/10, Time : 18:46:42
static const t_data g_all_data_step_12[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1498, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1491, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2528, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2972, .int_delta = 0}};

//Date : 2023/10/10, Time : 18:56:52
static const t_data g_all_data_step_13[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1491, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2659, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2973, .int_delta = 0}};

//FERMETURE COUVERCLE 1/5
//Date : 2023/10/10, Time : 19:07:02
static const t_data g_all_data_step_14[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1492, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2680, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2973, .int_delta = 0}};

//FERMETURE COUVERCLE 2/5
//Date : 2023/10/10, Time : 19:17:12
static const t_data g_all_data_step_15[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1501, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1492, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2651, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 30, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2972, .int_delta = 0}};

//FERMETURE COUVERCLE 3/5
//Date : 2023/10/10, Time : 19:27:22
static const t_data g_all_data_step_16[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1498, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1501, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1492, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2645, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 64, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//FERMETURE COUVERCLE 4/5
//Date : 2023/10/10, Time : 19:37:32
static const t_data g_all_data_step_17[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1501, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1492, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2354, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 96, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1653, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//FERMETURE COUVERCLE 5/5
//Date : 2023/10/10, Time : 19:47:42
static const t_data g_all_data_step_18[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1502, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1493, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2663, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 119, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2972, .int_delta = 0}};

//Date : 2023/10/10, Time : 19:57:52
static const t_data g_all_data_step_19[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1501, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1501, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1494, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2527, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1518, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2467, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2972, .int_delta = 0}};

//Date : 2023/10/10, Time : 20:29:23
static const t_data g_all_data_step_20[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1502, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1503, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1495, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2537, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2639, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 20:39:33
static const t_data g_all_data_step_21[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1503, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1503, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1495, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2524, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2467, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 20:49:43
static const t_data g_all_data_step_22[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1503, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1504, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1495, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2660, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 20:59:53
static const t_data g_all_data_step_23[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1503, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1505, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1496, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2587, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2467, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2972, .int_delta = 0}};

//Date : 2023/10/10, Time : 21:10:03
static const t_data g_all_data_step_24[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4016, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1504, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1505, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1496, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2649, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1518, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2467, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 21:20:13
static const t_data g_all_data_step_25[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1505, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1505, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1497, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2426, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 41, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2972, .int_delta = 0}};

//Date : 2023/10/10, Time : 21:30:23
static const t_data g_all_data_step_26[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4019, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1505, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1506, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1497, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2581, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 21:40:33
static const t_data g_all_data_step_27[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1506, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1507, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1498, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2522, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 21:50:43
static const t_data g_all_data_step_28[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1506, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1507, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2527, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/10, Time : 22:00:53
static const t_data g_all_data_step_29[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1506, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1507, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1499, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2715, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2972, .int_delta = 0}};

//Date : 2023/10/10, Time : 22:11:03
static const t_data g_all_data_step_30[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1507, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1508, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2568, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2639, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 22:21:13
static const t_data g_all_data_step_31[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1507, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1509, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2530, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2467, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 22:31:23
static const t_data g_all_data_step_32[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1508, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1509, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2499, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 44, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 22:40:33
static const t_data g_all_data_step_33[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1508, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1509, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1500, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2659, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 22:50:43
static const t_data g_all_data_step_34[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1509, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1510, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1501, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2518, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 23:00:53
static const t_data g_all_data_step_35[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1509, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1510, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1502, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 44, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/10, Time : 23:11:03
static const t_data g_all_data_step_36[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1510, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1510, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1503, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2444, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 42, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2321, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/10, Time : 23:21:13
static const t_data g_all_data_step_37[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1511, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1511, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1503, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2525, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/10, Time : 23:31:23
static const t_data g_all_data_step_38[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1511, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1512, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1504, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2727, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2969, .int_delta = 0}};

//Date : 2023/10/10, Time : 23:41:33
static const t_data g_all_data_step_39[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1512, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1512, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1504, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2584, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/10, Time : 23:51:43
static const t_data g_all_data_step_40[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1512, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1505, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/11, Time : 00:01:53
static const t_data g_all_data_step_41[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4019, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1504, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2539, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/11, Time : 00:11:03
static const t_data g_all_data_step_42[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4016, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1505, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2664, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/11, Time : 00:21:13
static const t_data g_all_data_step_43[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1506, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2625, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2969, .int_delta = 0}};

//Date : 2023/10/11, Time : 00:31:23
static const t_data g_all_data_step_44[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1507, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2674, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/11, Time : 00:41:33
static const t_data g_all_data_step_45[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1507, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2585, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/11, Time : 00:51:43
static const t_data g_all_data_step_46[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1507, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2663, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/11, Time : 01:01:53
static const t_data g_all_data_step_47[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1508, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2366, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 42, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2971, .int_delta = 0}};

//Date : 2023/10/11, Time : 01:12:03
static const t_data g_all_data_step_48[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1508, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2523, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 01:22:13
static const t_data g_all_data_step_49[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4016, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1509, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2580, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2970, .int_delta = 0}};

//Date : 2023/10/11, Time : 01:32:23
static const t_data g_all_data_step_50[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1518, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1509, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048574, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2526, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 01:42:33
static const t_data g_all_data_step_51[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1510, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2642, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2325, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 01:52:43
static const t_data g_all_data_step_52[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4016, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1518, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1511, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2591, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2969, .int_delta = 0}};

//Date : 2023/10/11, Time : 02:02:53
static const t_data g_all_data_step_53[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1511, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2667, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2969, .int_delta = 0}};

//Date : 2023/10/11, Time : 02:13:03
static const t_data g_all_data_step_54[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1512, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2527, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 44, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 02:23:13
static const t_data g_all_data_step_55[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1521, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1522, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2682, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 02:33:23
static const t_data g_all_data_step_56[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1521, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048574, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2546, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 02:43:33
static const t_data g_all_data_step_57[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1521, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1521, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2609, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1652, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2969, .int_delta = 0}};

//Date : 2023/10/11, Time : 02:53:43
static const t_data g_all_data_step_58[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1521, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1521, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1513, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2641, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1648, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2467, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2969, .int_delta = 0}};

//Date : 2023/10/11, Time : 03:02:53
static const t_data g_all_data_step_59[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1521, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1522, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2527, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 50, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 03:13:03
static const t_data g_all_data_step_60[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4019, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1522, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1523, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2707, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2969, .int_delta = 0}};

//Date : 2023/10/11, Time : 03:23:13
static const t_data g_all_data_step_61[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1523, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1523, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2539, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 03:33:23
static const t_data g_all_data_step_62[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1523, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1523, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048574, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2521, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 03:43:33
static const t_data g_all_data_step_63[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2544, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 03:53:43
static const t_data g_all_data_step_64[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2693, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 04:03:53
static const t_data g_all_data_step_65[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1526, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2519, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 44, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 04:14:03
static const t_data g_all_data_step_66[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1526, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1518, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2632, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2637, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 04:24:13
static const t_data g_all_data_step_67[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1518, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2525, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2969, .int_delta = 0}};

//Date : 2023/10/11, Time : 04:34:23
static const t_data g_all_data_step_68[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4019, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1526, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1526, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2571, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 04:44:33
static const t_data g_all_data_step_69[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1527, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1527, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2539, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2636, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 04:54:43
static const t_data g_all_data_step_70[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1527, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1519, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2671, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 05:04:53
static const t_data g_all_data_step_71[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4016, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1520, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2610, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 05:15:03
static const t_data g_all_data_step_72[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1530, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1520, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2440, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 43, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 05:25:13
static const t_data g_all_data_step_73[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1529, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1529, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1522, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2534, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 05:35:23
static const t_data g_all_data_step_74[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1529, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1530, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1522, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2620, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 05:45:33
static const t_data g_all_data_step_75[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1529, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1530, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1521, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2515, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 05:55:43
static const t_data g_all_data_step_76[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1529, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1531, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1522, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2543, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2969, .int_delta = 0}};

//Date : 2023/10/11, Time : 06:05:53
static const t_data g_all_data_step_77[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1530, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1531, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1522, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2572, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2968, .int_delta = 0}};

//Date : 2023/10/11, Time : 06:16:03
static const t_data g_all_data_step_78[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4016, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1531, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1531, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1523, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2555, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 06:26:13
static const t_data g_all_data_step_79[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4016, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1531, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1532, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1523, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2547, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 42, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 06:36:23
static const t_data g_all_data_step_80[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1531, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1532, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1523, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2588, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 06:46:33
static const t_data g_all_data_step_81[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1533, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1533, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1524, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048574, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2711, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 06:56:43
static const t_data g_all_data_step_82[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1532, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1533, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2638, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 07:06:53
static const t_data g_all_data_step_83[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1532, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1533, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1524, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2678, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 07:17:03
static const t_data g_all_data_step_84[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1532, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1533, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1524, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2659, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 07:27:13
static const t_data g_all_data_step_85[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4016, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1531, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1534, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1524, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2716, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 07:37:23
static const t_data g_all_data_step_86[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1533, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1534, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2548, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 07:47:33
static const t_data g_all_data_step_87[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1532, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1534, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1525, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2562, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1651, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 07:57:43
static const t_data g_all_data_step_88[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4019, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1532, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1526, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2610, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1517, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 08:07:53
static const t_data g_all_data_step_89[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1534, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1527, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2586, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 08:18:03
static const t_data g_all_data_step_90[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1526, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2668, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 08:28:13
static const t_data g_all_data_step_91[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1526, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2691, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2324, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 08:38:23
static const t_data g_all_data_step_92[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1534, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1537, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1527, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2537, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2635, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 08:48:33
static const t_data g_all_data_step_93[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1534, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1536, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1527, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2560, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 42, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2321, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 08:58:43
static const t_data g_all_data_step_94[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1534, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1526, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2557, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2632, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 09:08:53
static const t_data g_all_data_step_95[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1527, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2552, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 09:19:03
static const t_data g_all_data_step_96[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4018, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1536, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1527, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2717, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 09:29:13
static const t_data g_all_data_step_97[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1536, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2368, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 41, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 09:39:23
static const t_data g_all_data_step_98[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1536, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1537, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2546, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 42, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2632, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 09:49:33
static const t_data g_all_data_step_99[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1536, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2369, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 09:59:43
static const t_data g_all_data_step_100[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1537, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1527, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2560, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 43, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 10:09:53
static const t_data g_all_data_step_101[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1536, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2371, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 42, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2321, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 10:20:03
static const t_data g_all_data_step_102[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1536, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2917, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 55, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 65, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 10:30:13
static const t_data g_all_data_step_103[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1539, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1559, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1528, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 28757, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 15952, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 54, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 12960, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2321, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 10:40:23
static const t_data g_all_data_step_104[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1547, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1568, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1532, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 5043, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 12537, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1516, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2466, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2967, .int_delta = 0}};

//Date : 2023/10/11, Time : 10:50:33
static const t_data g_all_data_step_105[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1551, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1562, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 5056, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 12599, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2966, .int_delta = 0}};

//Date : 2023/10/11, Time : 11:00:43
static const t_data g_all_data_step_106[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1553, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1559, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1540, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2580, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 11:10:53
static const t_data g_all_data_step_107[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1552, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1558, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1541, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2548, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 11:21:03
static const t_data g_all_data_step_108[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1551, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1556, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1541, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2560, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 11:31:13
static const t_data g_all_data_step_109[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1549, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1554, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1541, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048574, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2674, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2321, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2632, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 11:41:23
static const t_data g_all_data_step_110[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1549, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1554, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1540, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2559, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2321, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 11:51:33
static const t_data g_all_data_step_111[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1548, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1552, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1539, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2748, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 12:01:43
static const t_data g_all_data_step_112[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1547, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1551, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1538, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2579, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 12:11:53
static const t_data g_all_data_step_113[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1546, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1550, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1538, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2563, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2323, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1648, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 12:22:03
static const t_data g_all_data_step_114[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1546, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1549, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1537, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2522, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 41, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2321, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1648, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 12:32:13
static const t_data g_all_data_step_115[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1545, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1548, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1537, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2689, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2321, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 12:42:23
static const t_data g_all_data_step_116[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1545, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1549, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1536, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2709, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2634, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 12:52:33
static const t_data g_all_data_step_117[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1545, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1548, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1537, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2614, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 49, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2965, .int_delta = 0}};

//Date : 2023/10/11, Time : 13:02:43
static const t_data g_all_data_step_118[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1545, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1546, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048574, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2549, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 48, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2632, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 13:12:53
static const t_data g_all_data_step_119[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1543, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1546, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1535, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2555, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 13:23:03
static const t_data g_all_data_step_120[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1541, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1545, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1533, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2533, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 13:33:13
static const t_data g_all_data_step_121[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1541, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1545, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1534, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 63, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2565, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 43, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 13:43:23
static const t_data g_all_data_step_122[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1542, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1544, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1534, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2675, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2963, .int_delta = 0}};

//Date : 2023/10/11, Time : 13:53:33
static const t_data g_all_data_step_123[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1540, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1544, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1533, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2585, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 47, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 14:03:43
static const t_data g_all_data_step_124[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1540, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1543, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1533, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 1048575, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2770, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 45, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2321, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2963, .int_delta = 0}};

//Date : 2023/10/11, Time : 14:13:53
static const t_data g_all_data_step_125[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1541, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1544, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1532, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2557, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2632, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 14:24:03
static const t_data g_all_data_step_126[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1540, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1542, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1531, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 52, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2703, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 50, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1649, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2963, .int_delta = 0}};

//Date : 2023/10/11, Time : 14:34:13
static const t_data g_all_data_step_127[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1540, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1542, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1531, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2665, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 46, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 7, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1515, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2465, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2964, .int_delta = 0}};

//Date : 2023/10/11, Time : 14:44:23
static const t_data g_all_data_step_128[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 4017, .int_delta = 0},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 11, .int_delta = 0},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 12, .int_delta = 0},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 1539, .int_delta = 0},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 1541, .int_delta = 0},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 1530, .int_delta = 0},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 62, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 2433, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 41, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 22, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 6, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 0, .int_delta = 0},//TODO : Manage negative values
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0},// 0 - 119
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 53, .int_delta = 0},// 0 - 53
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 1514, .int_delta = 0},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 2322, .int_delta = 0},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 1650, .int_delta = 0},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 2464, .int_delta = 0},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 2633, .int_delta = 0},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 2963, .int_delta = 0}};

// Donnees en passant par des etapes
static const t_data *g_all_data[] = {
	g_all_data_step_1, g_all_data_step_2, g_all_data_step_3, g_all_data_step_4, g_all_data_step_5, g_all_data_step_6, g_all_data_step_7, g_all_data_step_8, g_all_data_step_9, g_all_data_step_10, g_all_data_step_11, g_all_data_step_12, g_all_data_step_13, g_all_data_step_14, g_all_data_step_15, g_all_data_step_16, g_all_data_step_17, g_all_data_step_18, g_all_data_step_19, g_all_data_step_20, g_all_data_step_21, g_all_data_step_22, g_all_data_step_23, g_all_data_step_24, g_all_data_step_25, g_all_data_step_26, g_all_data_step_27, g_all_data_step_28, g_all_data_step_29, g_all_data_step_30, g_all_data_step_31, g_all_data_step_32, g_all_data_step_33, g_all_data_step_34, g_all_data_step_35, g_all_data_step_36, g_all_data_step_37, g_all_data_step_38, g_all_data_step_39, g_all_data_step_40, g_all_data_step_41, g_all_data_step_42, g_all_data_step_43, g_all_data_step_44, g_all_data_step_45, g_all_data_step_46, g_all_data_step_47, g_all_data_step_48, g_all_data_step_49, g_all_data_step_50, g_all_data_step_51, g_all_data_step_52, g_all_data_step_53, g_all_data_step_54, g_all_data_step_55, g_all_data_step_56, g_all_data_step_57, g_all_data_step_58, g_all_data_step_59, g_all_data_step_60, g_all_data_step_61, g_all_data_step_62, g_all_data_step_63, g_all_data_step_64, g_all_data_step_65, g_all_data_step_66, g_all_data_step_67, g_all_data_step_68, g_all_data_step_69, g_all_data_step_70, g_all_data_step_71, g_all_data_step_72, g_all_data_step_73, g_all_data_step_74, g_all_data_step_75, g_all_data_step_76, g_all_data_step_77, g_all_data_step_78, g_all_data_step_79, g_all_data_step_80, g_all_data_step_81, g_all_data_step_82, g_all_data_step_83, g_all_data_step_84, g_all_data_step_85, g_all_data_step_86, g_all_data_step_87, g_all_data_step_88, g_all_data_step_89, g_all_data_step_90, g_all_data_step_91, g_all_data_step_92, g_all_data_step_93, g_all_data_step_94, g_all_data_step_95, g_all_data_step_96, g_all_data_step_97, g_all_data_step_98, g_all_data_step_99, g_all_data_step_100, g_all_data_step_101, g_all_data_step_102, g_all_data_step_103, g_all_data_step_104, g_all_data_step_105, g_all_data_step_106, g_all_data_step_107, g_all_data_step_108, g_all_data_step_109, g_all_data_step_110, g_all_data_step_111, g_all_data_step_112, g_all_data_step_113, g_all_data_step_114, g_all_data_step_115, g_all_data_step_116, g_all_data_step_117, g_all_data_step_118, g_all_data_step_119, g_all_data_step_120, g_all_data_step_121, g_all_data_step_122, g_all_data_step_123, g_all_data_step_124, g_all_data_step_125, g_all_data_step_126, g_all_data_step_127, g_all_data_step_128};

typedef struct s_data_info
{
	t_data *datas;
	char *time;
} t_data_info;

void write_json(t_data_info *data, char *filename);

#endif
