void setup() {

  DDRB = 0b00100000;

}

void loop() {

  uint8_t pin;
  for(;;){
    pin = (1<<PINB4);
    pin &= (PINB);

    if(pin==0){
  	  PORTB = 0b00100000;
      asm ( "nop \n");
    }else{
  	  PORTB =0b00000000;
      asm ( "nop \n");
    }
  }
}