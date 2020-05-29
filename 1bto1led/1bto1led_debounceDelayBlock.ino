#define BTO 7
#define LED 12

bool status_led = false;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTO, INPUT_PULLUP); 
  digitalWrite(LED, status_led);   

}

void loop() {

	if(!digitalRead(BTO)){
 	 	delay(200);
 	 	if(!digitalRead(BTO)){
			status_led = !status_led;
			digitalWrite(LED, status_led);
		}
		while(!digitalRead(BTO));
  }

}
