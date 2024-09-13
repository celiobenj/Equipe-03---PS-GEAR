#include <Arduino.h>
#include "movimento.h"

void setup() {
	Serial.begin(9600);
	setupPins();
	delay(500);
}

void loop() {
	calcular_dist();
	
	frente();

	if (dist_dir < DIST_PAREDE || dist_esq < DIST_PAREDE){
		if (dist_esq < dist_dir){
			direita();
		} else {
			esquerda();
		}
	}

	if (dist_frente < DIST_PAREDE + 2){
		if (dist_esq < dist_dir){
			direita_90();
		} else {
			esquerda_90();
		}
	}

	delay(50);
	para();
	delay(50);
}
