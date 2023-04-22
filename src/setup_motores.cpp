#include "setup_motores.h"
#include "config.h"

// frequência otima para n20 500rpm - varia entre 1kHz e 20kHz, mais utilizados são entre 5kHz-10kHz
// taxa de bits varia entre 8-12 


// Funções presente nesse módulo
void init_motor(int In_A, int In_B, int pwm, int Canal);  // inicializar o motor
void set_rotation(int In_A, int In_B, int canal, int vel);  // irá controlar a direção de rotação do motor
void set_speed(int velE, int velD); // irá controlar a velocidade do motor
void setup_motor(); // irá inicializar os motores e será chamado na aba principal

void init_motor(int In_A, int In_B, int pwm, int Canal){
  pinMode(In_A, OUTPUT);
  pinMode(In_B, OUTPUT);
  ledcSetup(Canal,1000, 10);
  ledcAttachPin(pwm, Canal);
  ledcWrite(Canal, 0); 
  digitalWrite(In_A, LOW);
  digitalWrite(In_B, LOW);
  Serial.print(pwm);
  Serial.print(" Iniciado\n");
  }

void set_rotation(int In_A, int In_B, int canal, int vel){
  
  // se a velocidade for positiva faz o motor rotacionar para frente
  if (vel > 0){
    digitalWrite(In_A, HIGH);
    digitalWrite(In_B, LOW);
    }
  // se a velocidade for negativa faz o motor rotacionar no sentido inverso/para trás
  else if (vel < 0){
    digitalWrite(In_A, LOW);
    digitalWrite(In_B, HIGH);  
    }
  else {
    digitalWrite(In_A, LOW);
    digitalWrite(In_B, LOW);
    }
  ledcWrite(canal, abs(vel));
  }

void set_speed(int velE, int velD){
  set_rotation(Ain1, Ain2, 0, velE);
  set_rotation(Bin1, Bin2, 1, velD);
  }

void setup_motor(){
  init_motor(Ain1, Ain2, pwmA, PH1);
  init_motor(Bin1, Bin2, pwmB, PH2);
  }
