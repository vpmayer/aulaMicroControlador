void setup() {
  DDRB =  0b00100000;
  PORTB = 0b00100000;
}
const uint32_t delayValue = 200;
void myDelay(uint32_t ms);

void loop() {

  PORTB |= (1<<PB5);

  myDelay(delayValue); 

  PORTB &= ~(1<<PB5);

  myDelay(delayValue);
}

void myDelay(uint32_t ms){
  //F_CPU contem a informação da frequancia de cloque principal do uC
  //esse for consome 7 instruções de maquina no assembler
  //a instrução demora 1 ciclo de maquina, sondiderando F_CPU = 16000000
  // o loop roda a F_CPU/7 Hz = 2285714,2857 
  // 1 ms = 1/1000 Hz
  // portanto  a cada 2285,7142857 instruções ele consome 1 ms
  const uint32_t instMs = F_CPU/7000;
  uint32_t i;

  ms = ms * instMs;

  for(i=0; i<ms; i++){
    asm ( "nop \n");
  }

}

