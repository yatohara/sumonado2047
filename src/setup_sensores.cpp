// #include <Adafruit_VL53L0X.h>
#include "setup_sensores.h"
#include "config.h"

// A LOGICA DO TCRT É INVERTIDA, QUANDO DETECTA ALGO RETORNA 0 E QUANDO NÃO RETORNA 1

VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;



// Adafruit_VL53L0X sensor1 = Adafruit_VL53L0X();
// Adafruit_VL53L0X sensor2 = Adafruit_VL53L0X();
// Adafruit_VL53L0X sensor3 = Adafruit_VL53L0X();


// recebem os valores dos sensores
// VL53L0X_RangingMeasurementData_t sensor1_data;
// VL53L0X_RangingMeasurementData_t sensor2_data;
// VL53L0X_RangingMeasurementData_t sensor3_data;


// funcoes presentes

void init_sensor_lin(int sensor_pin); // inicializa o sensor de linha
void setup_sensor();  // inicializa todos os sensores
void setID();  // adiciona os endereços aos sensores VL 
int read_sensor_lin(int sensor_pin); // realiza a leitura dos sensores de linha
double read_front_sensor();  // retorna a leitura do VL do centro
double read_right_sensor();  // retorna a leitura do VL direito
double read_left_sensor();  // retorna a leitura do VL esquerdo


void setID() {
  // all reset
  // all unreset

  pinMode(SENSOR1_SHT_PIN, INPUT);
  sensor1.init(true);
  sensor1.setAddress(SENSOR1_ADDRESS);
  delay(20);

  pinMode(SENSOR2_SHT_PIN, INPUT);
  sensor2.init(true);
  sensor2.setAddress(SENSOR2_ADDRESS);
  delay(20);

  pinMode(SENSOR3_SHT_PIN, INPUT);
  sensor3.init(true);
  sensor3.setAddress(SENSOR3_ADDRESS);
  delay(20);

  sensor1.setTimeout(100);
  sensor2.setTimeout(100);
  sensor3.setTimeout(100);

//   digitalWrite(SENSOR1_SHT_PIN, HIGH);
//   digitalWrite(SENSOR2_SHT_PIN, HIGH);
//   digitalWrite(SENSOR3_SHT_PIN, HIGH);
//   delay(10);

//   // activating sensor1 and resetting sensor2 and sensor3
//   digitalWrite(SENSOR1_SHT_PIN, HIGH);
//   digitalWrite(SENSOR2_SHT_PIN, LOW);
//   digitalWrite(SENSOR3_SHT_PIN, LOW);

//   // initing sensor1
//   if(!sensor1.begin(SENSOR1_ADDRESS)) {
//     Serial.println(F("Failed to boot first VL53L0X"));
//     while(1);
//   }
//   delay(10);

//   // activating sensor2
//   digitalWrite(SENSOR2_SHT_PIN, HIGH);
//   delay(10);

//   //initing sensor2
//   if(!sensor2.begin(SENSOR2_ADDRESS)) {
//     Serial.println(F("Failed to boot second VL53L0X"));
//     while(1);
//   }
//   delay(10);


// // activating LOX3
//   digitalWrite(SENSOR3_SHT_PIN, HIGH);
//   delay(10);

//   //initing LOX3
//   if(!sensor3.begin(SENSOR3_ADDRESS)) {
//     Serial.println(F("Failed to boot third VL53L0X"));
//     while(1);
//   }  
}

double read_front_sensor() {
  return sensor1.readRangeSingleMillimeters();
  // int leitura1;
  // sensor1.rangingTest(&sensor1_data, false); // pass in 'true' to get debug data printout!
  // Serial.println("FRONT VL");
  // if(sensor1_data.RangeStatus != 4) {     // if not out of range
  //   leitura1 = sensor1_data.RangeMilliMeter;
  //   Serial.print(sensor1_data.RangeMilliMeter);
  //   return leitura1;
  // } else {
  //   Serial.print(F("Out of range"));
  //   return 0;
  // }
}

double read_right_sensor() {
  return sensor2.readRangeSingleMillimeters();
  // int leitura2;
  // sensor2.rangingTest(&sensor2_data, false); // pass in 'true' to get debug data printout!
  // Serial.print(F("RIGHT VL: "));
  // if(sensor2_data.RangeStatus != 4) {     // if not out of range
  //   leitura2 = sensor2_data.RangeMilliMeter;
  //   Serial.print(sensor2_data.RangeMilliMeter);
  //   return leitura2;
  // } else {
  //   Serial.print(F("Out of range"));
  //   return 0; 
  // }
}

double read_left_sensor() {
  return sensor3.readRangeSingleMillimeters();
  // int leitura3;
  // sensor3.rangingTest(&sensor3_data, false); // pass in 'true' to get debug data printout!
  // Serial.print(F("LEFT VL: "));
  // if(sensor3_data.RangeStatus != 4) {     // if not out of range
  //   leitura3 = sensor3_data.RangeMilliMeter;
  //   Serial.print(sensor3_data.RangeMilliMeter);
  //   return leitura3; 
  // } else {
  //   Serial.print(F("Out of range"));
  //   return 0;
  // }
}

void init_sensor_lin(int sensor_pin){
  pinMode(sensor_pin, INPUT); 
  delay(10); 
  }
 
int read_sensor_lin(int sensor_pin){
  return digitalRead(sensor_pin);
  }


void setup_sensor(){
  pinMode(SENSOR1_SHT_PIN, OUTPUT);
  pinMode(SENSOR2_SHT_PIN, OUTPUT);
  pinMode(SENSOR3_SHT_PIN, OUTPUT);
  pinMode(right_line_sensor, INPUT);
  pinMode(left_line_sensor, INPUT);

  Serial.println(F("Shutdown pins inited..."));

  digitalWrite(SENSOR1_SHT_PIN, LOW);
  digitalWrite(SENSOR2_SHT_PIN, LOW);
  digitalWrite(SENSOR3_SHT_PIN, LOW);

  
  Serial.println(F("Both in reset mode...(pins are low)"));
  Serial.println(F("Starting..."));
  setID();
  init_sensor_lin(right_line_sensor);
  init_sensor_lin(left_line_sensor);
  }
