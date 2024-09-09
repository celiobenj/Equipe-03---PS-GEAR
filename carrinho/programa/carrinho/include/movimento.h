#include <Arduino.h>
#include "Motor.h"
#include "Ultrassonico.h"

//! PINS
//MOTORES
#define PWM_MotorA 9
#define PWM_MotorB 10

#define IN1_MotorA 2
#define IN2_MotorA 3

#define IN1_MotorB 4
#define IN2_MotorB 5

//ULTRASSONICOS
#define TRIG1 A1
#define ECHO1 A0

//! MISCELÂNEA
#define MOTOR_OFF 0
#define MAX_POT 255

#define SENTIDO_CONTRA 2

//! OBJETOS
Motor motorA, motorB;


//! FUNÇÕES
void setupPins(){
    motorA.pinout(PWM_MotorA, IN1_MotorA, IN2_MotorA);
    motorB.pinout(PWM_MotorB, IN1_MotorB, IN2_MotorB);
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
