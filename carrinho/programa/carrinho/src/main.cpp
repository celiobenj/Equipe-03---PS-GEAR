#include <Arduino.h>
#include "movimento.h"

void setup() {
	Serial.begin(9600);
	setupPins();
}

void loop() {
	calcular_dist();
	frente();
	
	if (dist_frente < dist_parede || dist_dir < dist_parede || dist_esq < dist_parede){
		if (dist_esq > dist_dir){
			esquerda();
		}
		else {		
			direita();
		}
	}

	// if (dist_frente > dist_longe && dist_dir > dist_longe && dist_esq > dist_longe)	{
	// 	delay(4000);
	// 	while (true){
	// 		parar();
	// 		delay(10);
	// 	}
	// }
	delay(50);
}
