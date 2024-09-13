#include <Arduino.h>
#include <Ultrasonic.h>
#include "Motor.h"

#define DIST_PAREDE 8

double dist_frente, dist_esq, dist_dir;

//! PINS
//MOTORES
#define PWM_MotorD 9
#define PWM_MotorE 10

#define IN1_MotorD 3
#define IN2_MotorD 2

#define IN1_MotorE 4
#define IN2_MotorE 5

//ULTRASSONICOS
#define TRIG_FRENTE A3
#define ECHO_FRENTE A2

#define TRIG_DIR A4
#define ECHO_DIR A5

#define TRIG_ESQ A0
#define ECHO_ESQ A1

//! MISCELÂNEA
#define MOTOR_OFF 0
#define POT_D 135
#define POT_E 135

#define TEMPO_90 50


//! OBJETOS
Motor motorD, motorE;

Ultrasonic US_FRENTE(TRIG_FRENTE, ECHO_FRENTE);
Ultrasonic US_DIR(TRIG_DIR, ECHO_DIR);
Ultrasonic US_ESQ(TRIG_ESQ, ECHO_ESQ);

//! FUNÇÕES
void setupPins(){
    motorD.pinout(PWM_MotorD, IN1_MotorD, IN2_MotorD);
    motorE.pinout(PWM_MotorE, IN1_MotorE, IN2_MotorE);
}

void para(){
    motorD.write(0);
    motorE.write(0);
}

void frente(){
    motorD.write(POT_D);
    motorE.write(POT_E);
}

void esquerda(){
    motorD.write(0);
    motorE.write(POT_E);
}

void direita(){
    motorD.write(POT_D);
    motorE.write(0);
}

void esquerda_90(){
    motorD.write(-POT_D);
    motorE.write(POT_E);
    delay(TEMPO_90);
}

void direita_90(){
    motorD.write(POT_D);
    motorE.write(-POT_E);
    delay(TEMPO_90);
}

void calcular_dist(){
    dist_frente = US_FRENTE.read();;
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

void calcular_dist_2(){
    int soma_frente = 0;
    for (int i = 0; i < 10; i++){
        soma_frente += US_FRENTE.read();
    }

    int soma_dir = 0;
    for (int i = 0; i < 10; i++){
        soma_dir += US_DIR.read();
    }

    int soma_esq = 0;
    for (int i = 0; i < 10; i++){
        soma_esq += US_ESQ.read();
    }

    dist_frente = soma_frente/10;
	dist_dir = soma_dir/10;
	dist_esq = soma_esq/10;

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
