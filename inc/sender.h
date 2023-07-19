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

#define SAMPLES_NU 300 // NUMBER OF SAMPLES IN FILES
#define SAMPLE_RATE 2  // RATE LOOP IN SECONDS

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

static const t_data g_all_data_step_1[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 20, .int_delta = 20},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 59, .int_delta = 59},
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 26, .int_delta = 26},
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 512, .int_delta = 512}};

static const t_data g_all_data_step_2[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 59, .int_delta = 59},
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 26, .int_delta = 26},
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 512, .int_delta = 512}};

static const t_data g_all_data_step_3[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 3048, .int_delta = 48},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 2048, .int_delta = 2048},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 59, .int_delta = 59},
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 26, .int_delta = 26},
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 512, .int_delta = 512}};

static const t_data g_all_data_step_4[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 59, .int_delta = 59},
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 26, .int_delta = 26},
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 512, .int_delta = 512}};

static const t_data g_all_data_step_5[] = {
	(t_data){.name = "Photodiode_1", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_2", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_3", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_4", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_5", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Photodiode_6", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_1", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_2", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_3", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_4", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_5", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_6", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_7", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_8", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_9", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 3848, .int_delta = 48},
	(t_data){.name = "Temperature_10", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 2048, .int_delta = 48},
	(t_data){.name = "Microphone", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0},
	(t_data){.name = "Spectro_current", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Organ_current", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Vin_current", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Q7_current", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "5v_current", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "3.3v_current", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = 127, .int_delta = 127},
	(t_data){.name = "Motor_current", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = 32767, .int_delta = 32767},
	(t_data){.name = "Carousel_state", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 59, .int_delta = 59},
	(t_data){.name = "Lid_state", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 26, .int_delta = 26},
	(t_data){.name = "Organ_1", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_2", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_3", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_4", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_5", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = 512, .int_delta = 512},
	(t_data){.name = "Organ_6", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = 512, .int_delta = 512}};

// Donnees en passant par des etapes
static const t_data *g_all_data[] = {
	g_all_data_step_1, g_all_data_step_2, g_all_data_step_3, g_all_data_step_4, g_all_data_step_5};

typedef struct s_data_info
{
	t_data *datas;
	char *time;
} t_data_info;

void write_json(t_data_info *data, char *filename);

#endif
