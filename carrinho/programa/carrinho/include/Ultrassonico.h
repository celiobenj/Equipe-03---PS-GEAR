#include <Arduino.h>

class Ultrassonico{
    int trig, echo;

    public:
        void pinout(int pin_trig, int pin_echo){
            trig = pin_trig;
            echo = pin_echo;

            pinMode(trig, OUTPUT);
            pinMode(echo, INPUT);
        }

        int distancia(){
            unsigned long tempo = 0;
            int distancia = 0, soma = 0;
            const int amostras = 50;

            for (int i = 0; i < amostras; i++){
                while (distancia == 0) {
                    digitalWrite(trig, HIGH);
                    delayMicroseconds(10);
                    digitalWrite(trig, LOW);

                    tempo = pulseIn(echo, HIGH, 23529);
                    distancia = (tempo / 58.3);
                }

                soma += distancia;
            }

            return soma/amostras;
        }
};
