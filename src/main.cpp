#include <Wire.h>
#include <VL53L0X.h>
#include <Arduino.h>
#include <IRremote.h>

#include "motors/motors.h"

<<<<<<< HEAD
double sensor_front;
int line_right, line_left;
long rotate_start_time = 0;
long global_time = 0, rtime;
int comando;
=======
VL53L0X sensor;
Motors motors;
>>>>>>> 2295f6fbe8cb07cfe0b7dcdc2e95441d9182b07f

#define ledTeste 4
#define IR_RECEIVE_PIN 36

bool running = false;
unsigned long startTime = 0;
bool direcao = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();
  motors.setup();

<<<<<<< HEAD
// para teste do código
void loop(){
  rtime = millis() - global_time;

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

    estado = get_state(sensor_front, line_left, line_right, rtime);


    Serial.print("Sensor_front: ");
    Serial.println(sensor_front);

      
    switch (estado)
    {
      case search:
        Serial.println("PARA FRENTE");
        procurar();

      case rotate:
        Serial.println("RODANDO");
        rotacionar();

      case attack:
        Serial.println("ATACAR");
        atacar();

      break;
      default: procurar();
      } 
  }

  
else if (comando == IR_BUTTON3){
  set_speed(0, 0);
  }
=======
  pinMode(ledTeste, OUTPUT);
  digitalWrite(ledTeste, LOW);

  IrReceiver.begin(IR_RECEIVE_PIN);
>>>>>>> 2295f6fbe8cb07cfe0b7dcdc2e95441d9182b07f
}

void readControl() {
    if (IrReceiver.decode()){
        IrReceiver.resume();
        int command = IrReceiver.decodedIRData.command;
        Serial.print(command);
        digitalWrite(ledTeste, HIGH);
        delay(20);
        digitalWrite(ledTeste, LOW);
        if (command == 1) {
            startTime = millis();
            running = true;
        } else if (command == 2) running = false;     
    }
}

void loop(){
    if (running) {
        unsigned long relativeTime = millis() - startTime;
        Serial.println(sensor.readRangeContinuousMillimeters());
        if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

        if (sensor.readRangeContinuousMillimeters() < 400) {
            Serial.println("ATACAR");
            motors.write(255, 240);
            delay(200);
            if (sensor.readRangeContinuousMillimeters() < 250) {
                while (sensor.readRangeContinuousMillimeters() < 250) {
                    motors.write(255, 255);
                    readControl();
                    if (!running) return;
                }
            } else direcao = !direcao;
        } else {
            if (relativeTime <250) {
                Serial.println("FRENTE");
                motors.write(255, 255);
            } else {
                Serial.println("GIRAR");
                if (direcao) motors.write(-150, 150);
                else motors.write(150, -150);
            }
        }
    } else {
        motors.write(0, 0);
    }

    readControl();
}