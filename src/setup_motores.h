#ifndef _SETUP_MOTORES_H_
#define _SETUP_MOTORES_H_

#include "config.h"

void init_motor(int In_A, int In_B, int pwm, int Canal);  // inicializar o motor
void set_rotation(int In_A, int In_B, int canal, int vel);  // irá controlar a direção de rotação do motor
void set_speed(int velE, int velD); // irá controlar a velocidade do motor
void setup_motor(); // irá inicializar os motores e será chamado na aba principal

#endif