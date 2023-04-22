#ifndef _SETUP_SENSORES_H_
#define _SETUP_SENSORES_H_

#include "config.h"
#include <VL53L0X.h>

void init_sensor_lin(int sensor_pin); // inicializa o sensor de linha
void setup_sensor();  // inicializa todos os sensores
void setID();  // adiciona os endereços aos sensores VL 
int read_sensor_lin(int sensor_pin); // realiza a leitura dos sensores de linha
double read_front_sensor();  // retorna a leitura do VL do centro
double read_right_sensor();  // retorna a leitura do VL direito
double read_left_sensor();  // retorna a leitura do VL esquerdo


#endif