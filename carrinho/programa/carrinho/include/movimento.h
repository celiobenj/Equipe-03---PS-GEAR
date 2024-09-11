#include <Arduino.h>
#include "Motor.h"
#include "Ultrassonico.h"

//! PINS
//MOTORES
#define PWM_MotorA 9
#define PWM_MotorB 10

#define IN1_MotorA 3
#define IN2_MotorA 2

#define IN1_MotorB 4
#define IN2_MotorB 5

//ULTRASSONICOS
#define TRIG_FRENTE A3
#define ECHO_FRENTE A2

#define TRIG_DIR A4
#define ECHO_DIR A5

#define TRIG_ESQ A0
#define ECHO_ESQ A1

//! MISCELÂNEA
#define MOTOR_OFF 0
#define MAX_POT 80

#define SENTIDO_CONTRA 2

int dist_frente, dist_esq, dist_dir;

//! OBJETOS
Motor motorA, motorB;
Ultrassonico US_FRENTE, US_DIR, US_ESQ;

//! FUNÇÕES
void setupPins(){
    motorA.pinout(PWM_MotorA, IN1_MotorA, IN2_MotorA);
    motorB.pinout(PWM_MotorB, IN1_MotorB, IN2_MotorB);

    US_FRENTE.pinout(TRIG_FRENTE, ECHO_FRENTE);
	US_DIR.pinout(TRIG_DIR, ECHO_DIR);
	US_ESQ.pinout(TRIG_ESQ, ECHO_ESQ);
}

void parar(){
    motorA.write(MOTOR_OFF);
    motorB.write(MOTOR_OFF);
}

void frente(){
    motorA.write(MAX_POT);
    motorB.write(MAX_POT);
}

void costa(){
    motorA.write(MAX_POT, SENTIDO_CONTRA);
    motorB.write(MAX_POT, SENTIDO_CONTRA);
}

void direita(){
    motorA.write(MAX_POT);
    motorB.write(MAX_POT, SENTIDO_CONTRA);
}

void esquerda(){
    motorA.write(MAX_POT, SENTIDO_CONTRA);
    motorB.write(MAX_POT);
}

void calcular_dist(){
    dist_frente = US_FRENTE.distancia();
	dist_dir = US_DIR.distancia();
	dist_esq = US_ESQ.distancia();

    Serial.print("F:");
    Serial.print(dist_frente);
    Serial.print(" ");

    Serial.print("E:");
    Serial.print(dist_esq);
    Serial.print(" ");

    Serial.print("D:");
    Serial.print(dist_dir);
    Serial.print("\n");
}
