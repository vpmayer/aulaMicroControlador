#define BTO 7

byte disp0 = 0;
byte disp1 = 0;

bool selec_display = 0;

unsigned long time = 0;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(BTO, INPUT_PULLUP); 

  pinMode(6, OUTPUT);
  digitalWrite(6,selec_display);
}

void loop() {

  if((millis()-time) > 500){
    time = millis();
  	if(!digitalRead(BTO)){
  		if(++disp0 > 9){
  			disp0 = 0;
        if(++disp1 > 9)
          disp1=0;
      }
    }
	}


  if(selec_display)
    PORTB = disp0;
  else
    PORTB = disp1;

  selec_display = !selec_display;
  digitalWrite(6,selec_display);
  delay(10);
}
