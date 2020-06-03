#define LED_R A5
#define LED_Y A4
#define LED_G A3
#define TMP_PIN	A0
#define DISP_PIN	6

#define TimerLoader 65000



float temp = 0.0;
int tmp_digtal = 0;
byte disp0 = 0;
byte disp1 = 0;
bool select_display = false;


float convertTmp(int tmp);
void setTimer1();
void displays(int cont);



void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);

  pinMode(DISP_PIN, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  setTimer1();

  pinMode(TMP_PIN, INPUT);
  analogReference(EXTERNAL);
}



void loop() {

	tmp_digtal = analogRead(TMP_PIN);

	temp = convertTmp(tmp_digtal);

	displays((int)temp);

	if(temp < 37.0){
		digitalWrite(LED_G, HIGH);
		digitalWrite(LED_Y, LOW);
		digitalWrite(LED_R, LOW);
	} else{
		if (temp <= 38.0){
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_Y, HIGH);
			digitalWrite(LED_R, LOW);
		} else{
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_Y, LOW);
			digitalWrite(LED_R, HIGH);
		}
	}  

	delay(500);                  
}

float convertTmp(int tmp){
	float V;
	float graus;
	float Vref = 2.0;
	//tmp = 25.0 = 0.75V
	// Delta = 10 mV/°C
	// t(v) = (V/0.01) - 50
	
	// resolução = 5.0/1024 => aproximadamente 0.005volt/adc
	// adc = (Vin * 1024)/ Vre 
	// Vin = (adc*Vref)/1024
	V = (float)tmp; 
	V = (V * Vref);
	V = V/1024.0;

	graus = (V/0.01);
	graus = graus - 50.0;

	return graus;
}

void setTimer1(){
	cli(); // disable global interrupts

  TCCR1A = 0; // clear TCCR1A
  TCCR1B = 0; // clear TCCR1B

  TIMSK1 = (1 << TOIE1); // enable overflow interrupt
  TCCR1B |= (1 << CS12); // set prescale to F_CPU/256

  TCNT1 = TimerLoader; // pre load timer counter

  sei(); // enable global interrupts
}

void displays(int cont){

  disp0 = cont % 10;
  disp1 = cont / 10;

}

ISR(TIMER1_OVF_vect) {
	TCNT1 = TimerLoader; 

	if(!select_display)
    PORTB = disp0;
  else
    PORTB = disp1;

	digitalWrite(6,select_display);
	select_display = !select_display;
}
