#include <Wire.h>
#include <VL53L0X.h>
#include <Arduino.h>
#include <IRremote.h>

#include "motors/motors.h"

VL53L0X sensor;
Motors motors;

#define ledTeste 4
#define IR_RECEIVE_PIN 36
#define right_line_sensor 23
#define left_line_sensor 15

bool running = false;
bool direcao = false;
int strategy = 3;
unsigned long startTime = 0;
int right_line, left_line;

void line_sensor_setup();

void setup() {
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    digitalWrite(ledTeste, HIGH);
    while (1) {}
  } else {
    digitalWrite(ledTeste, LOW);
  }
  sensor.startContinuous();
  motors.setup();

  pinMode(ledTeste, OUTPUT);
  digitalWrite(ledTeste, LOW);

  IrReceiver.begin(IR_RECEIVE_PIN);
  line_sensor_setup();
}

void readControl() {
    if (IrReceiver.decode()){
        IrReceiver.resume();
        int command = IrReceiver.decodedIRData.command;
        Serial.print(command);
        if (command == 1) {
            startTime = millis();
            running = true;
        } else if (command == 2) { 
            running = false; 
        } else if (command > 2 && command < 10) {
            if (strategy != command) {
                for (int i = 0; i < command+1; i++) {
                    Serial.println(i);
                    digitalWrite(ledTeste, HIGH);
                    delay(150);
                    digitalWrite(ledTeste, LOW);
                    delay(150);
                }
                delay(1000);
            }
            strategy = command;
            Serial.print("estrategia: ");
            Serial.println(strategy);
        }
        digitalWrite(ledTeste, HIGH);
        delay(20);
        digitalWrite(ledTeste, LOW);
    }
}

void loop(){
    if (running) {
        unsigned long relativeTime = millis() - startTime;
        Serial.println(sensor.readRangeContinuousMillimeters());
        if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

        Serial.print("linha ");
        Serial.print(digitalRead(left_line_sensor));
        Serial.print("  ");
        Serial.println(digitalRead(right_line_sensor));


        if (sensor.readRangeContinuousMillimeters() < 400) {
            Serial.println("ATACAR");
            motors.write(255, 20);
            delay(100);
            motors.write(255, 255);
            delay(200);
            if (sensor.readRangeContinuousMillimeters() < 250) {
                while (sensor.readRangeContinuousMillimeters() < 250) {
                    motors.write(255, 255);
                    readControl();
                    if (!running) return;
                }
            } else direcao = !direcao;
        } else {
            // 4 -- detecta linha
            if (strategy == 3) {

            // 5 -- gira mais divagar
            } else if (strategy == 4) {
                if (relativeTime < 250) {
                    Serial.println("FRENTE");
                    motors.write(255, 240);
                } else {
                    Serial.println("GIRAR");
                    if (direcao) motors.write(-90, 90);
                    else motors.write(90, -90);
                }
            // 6 -- andar girand0
            } else if (strategy == 5) {
                if (relativeTime < 500) {
                    motors.write(80, 255);
                } else if (relativeTime < 1000) {
                    motors.write(250, 80);
                } else if (relativeTime < 1500) {
                    motors.write(80, 250);
                } else {
                    if (direcao) motors.write(-90, 90);
                    else motors.write(90, -90);
                }
            // 7 -- girando
            } else if (strategy == 6) {
                if (relativeTime < 150) {
                    motors.write(0, 240);
                } else if (relativeTime < 1000) {
                    motors.write(250, 0);
                } else if (relativeTime < 2000) {
                    motors.write(0, 250);
                } else {
                    if (direcao) motors.write(-150, 150);
                    else motors.write(50, 250);
                }
            // 8 -- girando
            } else if (strategy == 7) {
                if (relativeTime < 500) {
                    motors.write(100, 255);
                } else {
                    if (direcao) motors.write(-150, 150);
                    else motors.write(50, 250);
                }
            // padrão
            } else {
                if (relativeTime < 250) {
                    Serial.println("FRENTE");
                    motors.write(255, 240);
                } else {
                    Serial.println("GIRAR");
                    if (direcao) motors.write(-150, 150);
                    else motors.write(150, -150);
                }
            }
        }
    } else {
        motors.write(0, 0);
    }

    readControl();
}

void line_sensor_setup(){
    pinMode(right_line_sensor, INPUT);
    pinMode(left_line_sensor, INPUT);
}
