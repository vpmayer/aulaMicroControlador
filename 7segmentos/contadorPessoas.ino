#include <avr/io.h>
#include <avr/interrupt.h>

#define BTO_IN 2
#define BTO_OUT 3

#define TimerLoader 65000

bool select_display = false;
byte disp0 = 0;
byte disp1 = 0;

volatile int pessoa = 0;

void contPessoa(int cont);
void maisUm();
void menosUm();

void setup() {
	pinMode(6, OUTPUT);
	pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTO_IN), maisUm, FALLING); //pino 2
  attachInterrupt(digitalPinToInterrupt(BTO_OUT), menosUm, RISING); //pino 3

  cli(); // disable global interrupts

  TCCR1A = 0; // clear TCCR1A
  TCCR1B = 0; // clear TCCR1B

  TIMSK1 = (1 << TOIE1); // enable overflow interrupt
  TCCR1B |= (1 << CS12); // set prescale to F_CPU/256

  TCNT1 = TimerLoader; // pre load timer counter

  sei(); // enable global interrupts
}




void loop() {

	contPessoa(pessoa);

	delay(1000);
}

ISR(TIMER1_OVF_vect) {
	TCNT1 = TimerLoader; 

	if(!select_display)
    PORTB = disp0;
  else
    PORTB = disp1;

	digitalWrite(6,select_display);
	select_display = !select_display;
}

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