#define BTO 7
#define LED 12
#define MAX_DEBOUNCE 10000

bool status_led = false;
unsigned int debounce = MAX_DEBOUNCE; // que numero utilizar?

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTO, INPUT_PULLUP); 
  digitalWrite(LED, status_led);   

}

void loop() {
	debounce = MAX_DEBOUNCE;

  while(!digitalRead(BTO)){
		if(!digitalRead(BTO)){
			if(debounce != 0){
				debounce--;
			}
			else{
				status_led = !status_led;
  			digitalWrite(LED, status_led);
  			while(!digitalRead(BTO));
			}
		} 
  }

}
