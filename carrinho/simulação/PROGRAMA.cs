const int POT = 200;
int VEL_base = 100;

// PID
const double dist_desejada = 3.5;
const double kp = 6.0, ki = 0.7, kd = 2.0;

double ki_total_dir = 0.0;
double erro_anterior_dir = 0.0;

double ki_total_esq = 0.0;
double erro_anterior_esq = 0.0;

const double dist_parede = 4;
const double dist_parede_frente = 8;
double dist_frente, dist_esq, dist_dir;

Servomotor motorD = Bot.GetComponent<Servomotor>( "motorD" );
Servomotor motorE = Bot.GetComponent<Servomotor>( "motorE" );	

UltrasonicSensor US_frente = Bot.GetComponent<UltrasonicSensor>( "US_frente" );
UltrasonicSensor US_esq = Bot.GetComponent<UltrasonicSensor>( "US_esq" );
UltrasonicSensor US_dir = Bot.GetComponent<UltrasonicSensor>( "US_dir" );

async Task Main(){
	IO.OpenConsole();
	motorD.Locked = false;
	motorE.Locked = false;
	while (true){
		IO.ClearPrint();
		calc_dist();
		int velD = 400, velE = 400;
		
		if (dist_frente < dist_parede_frente || dist_dir < dist_parede || dist_esq < dist_parede){
			if (dist_esq < dist_dir){
				double PID = calc_PID_dir();
				velD = (int) (VEL_base + PID);
				velE = (int) (VEL_base - PID);
			} else {
				double PID = calc_PID_esq();
				velD = (int) (VEL_base - PID);
				velE = (int) (VEL_base + PID);
			}
			if (velD < 50 && velD > 0) velD = 50;
			else if (velD > 400) velD = 400;
			else if (velD < -400) velD = -400;

			if (velE < 100 && velE > 0) velE = -velE;
			else if (velE > -100 && velE < 0) velE = -velE;
			else if (velE > 400) velE = 400;
			else if (velE < -400) velE = -400;
		}
		
		if (dist_frente < dist_parede_frente && dist_dir < dist_parede + 1 && dist_esq < dist_parede + 1){
			velD = 400;
			velE = -400;
			direcao(velD, velE);
			await Time.Delay(3000);
			continue;
		}
		
		IO.PrintLine("velE: " + velE.ToString());
		IO.PrintLine("velD: " + velD.ToString());
		direcao(velD, velE);
		await Time.Delay(50);
	}
}

double calc_PID_dir(){
	
	double erro = dist_desejada - dist_dir;

	double P = kp * erro;

	ki_total_dir += erro;
	double I = ki * ki_total_dir;

	double D = kd * (erro - erro_anterior_esq);
	erro_anterior_dir = erro;

	ki_total_esq = 0.0;
	erro_anterior_esq = 0.0;

	IO.PrintLine("erro: " + erro.ToString());
	IO.PrintLine("P: " + P.ToString());
	IO.PrintLine("I: " + I.ToString());
	IO.PrintLine("D: " + D.ToString());
	IO.PrintLine("PID: " + (P + I + D).ToString());

	return P + I + D;
}

double calc_PID_esq(){
	
	double erro = dist_desejada - dist_esq; 

	double P = kp * erro;

	ki_total_esq += erro;
	double I = ki * ki_total_esq;

	double D = kd * (erro - erro_anterior_esq);
	erro_anterior_esq = erro;

	ki_total_dir = 0.0;
	erro_anterior_dir = 0.0;

	IO.PrintLine("erro: " + erro.ToString());
	IO.PrintLine("P: " + P.ToString());
	IO.PrintLine("I: " + I.ToString());
	IO.PrintLine("D: " + D.ToString());
	IO.PrintLine("PID: " + (P + I + D).ToString());

	return P + I + D;
}

void calc_dist(){
	dist_frente = US_frente.Analog;
	dist_esq = US_esq.Analog;
	dist_dir = US_dir.Analog;

	if (dist_frente == -1) dist_frente = 30;
	if (dist_esq == -1) dist_esq = 30;
	if (dist_dir == -1) dist_dir = 30;

	IO.PrintLine("dist_frente: " + dist_frente.ToString());
	IO.PrintLine("dist_dir: " + dist_dir.ToString());
	IO.PrintLine("dist_esq: " + dist_esq.ToString());
}

void direcao(int velD, int velE){
	motorD.Apply( POT , velD );
	motorE.Apply( POT , velE );
}