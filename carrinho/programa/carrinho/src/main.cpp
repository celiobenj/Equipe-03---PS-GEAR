#include <Arduino.h>
#include "movimento.h"

void setup() {
	Serial.begin(9600);
	setupPins();
}

void loop() {
	calcular_dist();
	frente();
	
	if (dist_frente < 8 || dist_dir < 8 || dist_esq < 8){
		if (dist_esq > dist_dir){
			esquerda();
			delay(10);
		}
		else {		
			direita();
			delay(10);
		}
	}

	if (dist_frente > 30 && dist_dir > 30 && dist_esq > 30)	{
		delay(4000);
		while (true){
			parar();
		}
	}
	delay(200);
}
