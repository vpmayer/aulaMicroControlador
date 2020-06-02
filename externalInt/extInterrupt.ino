int led_R = 13;
int led_B = 12;
int bto_0 = 2;
int bto_1 = 3; 

volatile int stateR = LOW;
volatile int stateB = LOW;

void setup(){

	pinMode(led_R, OUTPUT);
	pinMode(led_B, OUTPUT);

	attachInterrupt(digitalPinToInterrupt(bto_0), led_on, FALLING); //pino 2
	attachInterrupt(digitalPinToInterrupt(bto_1), led_off, RISING); //pino 3
}


void loop(){
	digitalWrite(led_B, stateB);
	delay(2500);
	stateB = !stateB;
}

void led_on(){
	stateR = HIGH;
	digitalWrite(led_R, stateR);
}
void led_off(){
	stateR = LOW;
	digitalWrite(led_R, stateR);
}