#include <avr/io.h>
#include <avr/interrupt.h>
#include <SPI.h>

#define TimerLoader 65000

bool select_display = false;
byte disp0 = 0;
byte disp1 = 0;

volatile int pessoa = 22;

void contPessoa(int cont);
void maisUm();
void menosUm();

void setup() {
	pinMode(6, OUTPUT);
	pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);

  cli(); // disable global interrupts

  TCCR1A = 0; // clear TCCR1A
  TCCR1B = 0; // clear TCCR1B

  TIMSK1 = (1 << TOIE1); // enable overflow interrupt
  TCCR1B |= (1 << CS12); // set prescale to F_CPU/256

  TCNT1 = TimerLoader; // pre load timer counter

  sei(); // enable global interrupts

  //Setup SPI SLAVE
  pinMode(SS, INPUT);
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);

}


void loop() {

	contPessoa(pessoa);

	delay(1000);
}

ISR(TIMER1_OVF_vect) {
	TCNT1 = TimerLoader; 

	if(!select_display)
    PORTC = disp0;
  else
    PORTC = disp1;

	digitalWrite(6,select_display);
	select_display = !select_display;
}



ISR (SPI_STC_vect)
{
  byte c = SPDR;
 
  pessoa = c;

}  // end of interrupt service routine (ISR) SPI_STC_vect


void contPessoa(int cont){

  disp0 = cont % 10;
  disp1 = cont / 10;

}

void maisUm(){
  if(pessoa<99)
    pessoa++;
}

void menosUm(){
  if(pessoa>0)
    pessoa--;
}