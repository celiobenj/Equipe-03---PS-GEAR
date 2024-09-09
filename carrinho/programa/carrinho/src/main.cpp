#include <Arduino.h>
#include "Ultrassonico.h"
#include "movimento.h"

Ultrassonico US1;

void setup() {
	Serial.begin(9600);
	US1.pinout(TRIG1, ECHO1);
	// setupPins();
}

void loop() {
	int dist = US1.distancia();
	Serial.println(dist);
	delay(100);
	// frente(1000);
	// costa(1000);
	// direita(1000);
	// esquerda(1000);
	// parar(1000);
}
