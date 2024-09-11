const int POT = 200;
const int VEL = 250;

const float dist_parede = 6;

double dist_frente, dist_esq, dist_dir;

Servomotor motorA = Bot.GetComponent<Servomotor>( "motorA" );
Servomotor motorB = Bot.GetComponent<Servomotor>( "motorB" );	

UltrasonicSensor US_frente = Bot.GetComponent<UltrasonicSensor>( "US_frente" );
UltrasonicSensor US_esq = Bot.GetComponent<UltrasonicSensor>( "US_esq" );
UltrasonicSensor US_dir = Bot.GetComponent<UltrasonicSensor>( "US_dir" );

async Task Main(){
	IO.OpenConsole();
	while (true){
		calcularDistancia();
		while (dist_frente >= dist_parede - 2 && dist_esq <= dist_parede && dist_dir <= dist_parede){
			frente();
			calcularDistancia();
			await Time.Delay(10);
			IO.ClearPrint();
		}
		while (dist_frente <= dist_parede - 2 && dist_esq >= dist_parede && dist_dir <= dist_parede){
			esquerda();
			calcularDistancia();
			await Time.Delay(10);
			IO.ClearPrint();
		}
		while (dist_frente <= dist_parede - 2 && dist_esq <= dist_parede && dist_dir >= dist_parede){
			direita();
			calcularDistancia();
			await Time.Delay(10);
			IO.ClearPrint();
		}
		while (dist_frente <= dist_parede - 2 && dist_esq <= dist_parede && dist_dir <= dist_parede){
			direita();
			calcularDistancia();
			await Time.Delay(500);
			IO.ClearPrint();
		}

		await Time.Delay(100);
		IO.ClearPrint();
	}
}

void calcularDistancia(){
	dist_frente = US_frente.Analog;
	dist_esq = US_esq.Analog;
	dist_dir = US_dir.Analog;
	
	IO.PrintLine("Frente: " + dist_frente.ToString());
	IO.PrintLine("Esquerda: " + dist_esq.ToString());
	IO.PrintLine("Direita: " + dist_dir.ToString());
}

void frente(){
	motorA.Apply( POT , VEL );
	motorB.Apply( POT , VEL );

	motorA.Locked = false;
	motorB.Locked = false;
}

void esquerda(){
	motorA.Apply( POT , VEL );
	motorB.Apply( POT , -VEL );

	motorA.Locked = false;
	motorB.Locked = false;
}

void direita(){
	motorA.Apply( POT , -VEL );
	motorB.Apply( POT , VEL );

	motorA.Locked = false;
	motorB.Locked = false;
}

void costa(){
	motorA.Apply( POT , -VEL );
	motorB.Apply( POT , -VEL );

	motorA.Locked = false;
	motorB.Locked = false;
}

void parar(){
	motorA.Locked = true;
	motorB.Locked = true;
}