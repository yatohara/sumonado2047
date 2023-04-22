#include <Wire.h>
#include <VL53L0X.h>
#include <Arduino.h>
#include <IRremote.h>

#include "motors/motors.h"

VL53L0X sensor;
Motors motors;

#define ledTeste 4
#define IR_RECEIVE_PIN 36

bool running = false;
unsigned long startTime = 0;
bool direcao = false;
void line_sensor_setup();
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

  pinMode(ledTeste, OUTPUT);
  digitalWrite(ledTeste, LOW);

  IrReceiver.begin(IR_RECEIVE_PIN);
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