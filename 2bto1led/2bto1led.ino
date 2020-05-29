#define BTO_D 6
#define BTO_E 7
#define LED_V 11


void setup() {
  pinMode(LED_V, OUTPUT);
  pinMode(BTO_D, INPUT);
  pinMode(BTO_E, INPUT_PULLUP);

}

void loop() {

	if(!digitalRead(BTO_E))
  	digitalWrite(LED_V, HIGH);   

	if(!digitalRead(BTO_D))
  	digitalWrite(LED_V, LOW);                           

}
