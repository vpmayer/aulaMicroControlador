void setup() {
  DDRB = 0b00100000;
  PORTB = 0b00100000;

}

void loop() {
//  uint32_t cont=16000000;
  uint32_t cont=2285714;
  uint32_t i=0;

  PORTB |= (1<<PB5);

  for(i=0; i<cont; i++){
    asm ( "nop \n");
  }

  PORTB &= ~(1<<PB5);

  for(i=0; i<cont; i++){
    asm ( "nop \n");
  }
}
