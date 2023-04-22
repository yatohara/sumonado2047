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
long global_time = 0, rtime;
int comando;


states estado;
void pisca_pisca();

void setup(){
  Serial.begin(SERIAL_RATE);
  Wire.begin(SDA, SCL);
  IrReceiver.begin(IRRECEPTOR);

  global_time = millis();
  pinMode(LED_TESTE, OUTPUT);
  digitalWrite(LED_TESTE, LOW);
  setup_sensor();
  setup_motor();
  }

// para teste do código
void loop(){
  rtime = millis();

  if (IrReceiver.decode()){
    IrReceiver.resume();

    comando = IrReceiver.decodedIRData.command;
    Serial.print(comando);
  }

    
  if ((comando == IR_BUTTON1)){
    pisca_pisca();
  }

  else if (comando == IR_BUTTON2){
    Serial.println("START");
    pisca_pisca();
    // sensor_front = read_front_sensor();
    // sensor_right = read_right_sensor();
    // sensor_left = read_left_sensor();
    line_right = read_sensor_lin(right_line_sensor);
    line_left = read_sensor_lin(left_line_sensor); 
    // int ajuste = ajuste_sumonado(sensor_left, sensor_right, sensor_front);

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
        Serial.println("PARA FRENTE");
        set_speed(-255, 255);
        procurar();

      case rotate:
        Serial.println("RODANDO");
        rotacionar();
        rotate_start_time = millis();


      // case attack:
      //   Serial.println("ATACAR");
      //   set_speed(-255, 255);
        //atacar(ajuste);

      break;
      default: procurar();
      } 
  }

  
else if (comando == IR_BUTTON3){
  set_speed(0, 0);
  }
}

void pisca_pisca(){
  digitalWrite(LED_TESTE, HIGH);
  delay(10);
  digitalWrite(LED_TESTE, LOW);
}