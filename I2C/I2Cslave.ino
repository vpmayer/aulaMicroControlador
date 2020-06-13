#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>

#define TimerLoader 65000

bool select_display = false;
byte disp0 = 0;
byte disp1 = 0;

volatile int pessoa = 0;

void contPessoa(int cont);
void receiveEvent(int howMany);


void setup() {
	pinMode(6, OUTPUT);
	pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  cli(); // disable global interrupts

  TCCR1A = 0; // clear TCCR1A
  TCCR1B = 0; // clear TCCR1B

  TIMSK1 = (1 << TOIE1); // enable overflow interrupt
  TCCR1B |= (1 << CS12); // set prescale to F_CPU/256

  TCNT1 = TimerLoader; // pre load timer counter

  sei(); // enable global interrupts

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
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


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
  }
  pessoa = Wire.read();    // receive byte as an integer
}

void contPessoa(int cont){

  disp0 = cont % 10;
  disp1 = cont / 10;

}