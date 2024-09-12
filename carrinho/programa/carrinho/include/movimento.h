#include <Arduino.h>
#include <Ultrasonic.h>
#include "Motor.h"

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
#define POT_A 75 
#define POT_B 75 

#define SENTIDO_CONTRA 2

#define TEMPO_90 1000

float dist_frente, dist_esq, dist_dir;
const float dist_parede = 10, dist_longe = 100;

//! OBJETOS
Motor motorA, motorB;

Ultrasonic US_FRENTE(TRIG_FRENTE, ECHO_FRENTE);
Ultrasonic US_DIR(TRIG_DIR, ECHO_DIR);
Ultrasonic US_ESQ(TRIG_ESQ, ECHO_ESQ);

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
    motorA.write(POT_A);
    motorB.write(POT_B);
}

void costa(){
    motorA.write(POT_A, SENTIDO_CONTRA);
    motorB.write(POT_B, SENTIDO_CONTRA);
}

void direita(){
    motorA.write(POT_A);
    motorB.write(MOTOR_OFF);
}

void esquerda(){
    motorA.write(MOTOR_OFF);
    motorB.write(POT_B);
}

void calcular_dist(){
    dist_frente = US_FRENTE.read();
	dist_dir = US_DIR.read();
	dist_esq = US_ESQ.read();

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
