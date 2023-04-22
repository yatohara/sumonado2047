#ifndef _CONFIG_H_
#define _CONFIG_H_

// bibliotecas 
#include <Arduino.h>

// comunicação infravermelho
#define IRRECEPTOR 36
#define SDA 21
#define SCL 22


//motoresDireitos
#define Ain1 13
#define Ain2 12
#define pwmA 14
#define PH1 0

//motoresEsquerdos
#define Bin1 25
#define Bin2 26
#define pwmB 27
#define PH2  1

//sensor VL

#define SENSOR1_ADDRESS 0x23
#define SENSOR2_ADDRESS 0x25
#define SENSOR3_ADDRESS 0x27

#define SENSOR1_SHT_PIN 5
#define SENSOR2_SHT_PIN 19
#define SENSOR3_SHT_PIN 18

// TCRT

#define right_line_sensor 23
#define left_line_sensor 15


//Geral 
#define LED_TESTE 4
#define SERIAL_RATE 9600

#endif