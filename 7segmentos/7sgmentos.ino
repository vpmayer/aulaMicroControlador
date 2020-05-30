#define BTO 7

byte cont = 0;
bool display = false;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(BTO, INPUT_PULLUP); 

  pinMode(6, OUTPUT);
  digitalWrite(6,LOW);
}

void loop() {


	if(!digitalRead(BTO)){

		if(++cont > 9){
			cont = 0;
			display = !display;
			digitalWrite(6,display);
		}
		PORTB = cont;

	}

  delay(500);
}
