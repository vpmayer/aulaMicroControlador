#define BTO 7
#define LED_R 13
#define LED_G 12
#define LED_B 11

byte collors = 0;
byte collor_cont = 0;


void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BTO, INPUT_PULLUP); 
}

void loop() {


	if(!digitalRead(BTO)){
		
		collor_cont++;

		digitalWrite(LED_R, (collor_cont & 0b00000001));
		digitalWrite(LED_G, (collor_cont & 0b00000010));
		digitalWrite(LED_B, (collor_cont & 0b00000100));

	}

  delay(500);
}
