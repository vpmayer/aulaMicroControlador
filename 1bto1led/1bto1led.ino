#define BTO 7
#define LED 12


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTO, INPUT); // sera que esta faltando alguma coisa?

}

bool status_led = false;

void loop() {
  	
  digitalWrite(LED, status_led);   

	if(!digitalRead(BTO))
		status_led = !status_led;

	//Ruido de sinal???...
}
