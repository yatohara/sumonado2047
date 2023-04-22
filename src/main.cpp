// Marcus esteve por aqui
#include "config.h"
#include "setup_motores.h"
#include "machine_state.h"
#include "setup_sensores.h"
#include <IRremote.h>
#include <Wire.h>

#define IR_BUTTON1 0
#define IR_BUTTON2 1
#define IR_BUTTON3 2  

double sensor_front, sensor_right, sensor_left;
int line_right, line_left;
int ajuste; 
long rotate_start_time = 0;
int c = 0;
int comando;


states estado;
void pisca_pisca();

void setup(){
  Serial.begin(SERIAL_RATE);
  Wire.begin(SDA, SCL);
  IrReceiver.begin(IRRECEPTOR);
  pinMode(LED_TESTE, OUTPUT);
  digitalWrite(LED_TESTE, LOW);
  setup_sensor();
  setup_motor();
  //setup_drv();
  }

// para teste do código
void loop(){


  if (IrReceiver.decode()){
    IrReceiver.resume();

    comando = IrReceiver.decodedIRData.command;
    Serial.print(comando);
  }

    
  if ((comando == IR_BUTTON1)){
    pisca_pisca();
  }

  else if (comando == IR_BUTTON2){
    c = 0;
    pisca_pisca();
    sensor_front = read_front_sensor();
    sensor_right = read_right_sensor();
    sensor_left = read_left_sensor();
    // line_right = read_sensor_lin(right_line_sensor);
    // line_left = read_sensor_lin(left_line_sensor); 
    line_right = 1;
    line_left = 1;
    int ajuste = ajuste_sumonado(sensor_left, sensor_right, sensor_front);
    estado = get_state(sensor_left, sensor_right, sensor_front, line_left, line_right, rotate_start_time);


    Serial.print("Sensor_front: ");
    Serial.print(sensor_front);
    Serial.print(" ");
    Serial.print("Sensor_left: ");
    Serial.print(sensor_left);
    Serial.print(" ");
    Serial.print("Sensor_right: ");
    Serial.print(sensor_right); 
    Serial.print(" \n");
    
      
    switch (estado)
    {
      case search:
        procurar();

      case rotate:
        rotacionar();
        rotate_start_time = millis();
      case attack:
        atacar(ajuste);

      break;
      default: procurar();
      } 
  }

  
else if (comando == 2){
  set_speed(0, 0);
  }
}

void pisca_pisca(){
  if (c < 20){
  digitalWrite(LED_TESTE, HIGH);
  delay(10);
  digitalWrite(LED_TESTE, LOW);
  c++;
  }
}