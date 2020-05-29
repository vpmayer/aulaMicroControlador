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
	

	if(!digitalRead(BTO)){
		
		debounce--;
		
		if(debounce == 0){
			status_led = !status_led;
			digitalWrite(LED, status_led);
		}
	} else{
		debounce = MAX_DEBOUNCE;
	}
  
}
