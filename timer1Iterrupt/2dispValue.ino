#include <avr/io.h>
#include <avr/interrupt.h>

#define BTO 7

#define TimerLoader 65000


void setup() {
	pinMode(6, OUTPUT);
	pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(BTO, INPUT_PULLUP);

  cli(); // disable global interrupts

  TCCR1A = 0; // clear TCCR1A
  TCCR1B = 0; // clear TCCR1B

  TIMSK1 = (1 << TOIE1); // enable overflow interrupt
  TCCR1B |= (1 << CS12); // set prescale to F_CPU/256

  TCNT1 = TimerLoader; // pre load timer counter

  sei(); // enable global interrupts
}

bool select_display = false;
byte disp0 = 0;
byte disp1 = 0;


void loop() {

	while(!digitalRead(BTO)){
		delay(100);
	}

	if(++disp0 > 9){
		disp0 = 0;
    if(++disp1 > 9)
      disp1=0;
  }

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
