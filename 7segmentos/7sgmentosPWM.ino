#define BTO 7

byte disp0 = 0;
byte disp1 = 0;

unsigned long time = 0;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(BTO, INPUT_PULLUP); 

  pinMode(6, OUTPUT);
  analogWrite(6,127);
}

void loop() {

  if((millis()-time) > 500){
  	if((PIND&(1<<PIND7)) == 0){
  		if(++disp0 > 9){
  			disp0 = 0;
        if(++disp1 > 0)
          disp1=0;
      }
    }
	}


    if((PIND&(1<<PIND6) )== 0)
      PORTB = disp0;
    else
      PORTB = disp1;

}
