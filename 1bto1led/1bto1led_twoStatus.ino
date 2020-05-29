#define BTO 7
#define LED 12


bool status_led = false;
bool last_status_led = false;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTO, INPUT_PULLUP); 
  digitalWrite(LED, status_led);   

}

void loop() {


	if(!digitalRead(BTO)){
		status_led = !last_status_led;
		digitalWrite(LED, status_led);
	} else{
		last_status_led = status_led;
	}

}
