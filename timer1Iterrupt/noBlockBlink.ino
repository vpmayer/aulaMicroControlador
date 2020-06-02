#include <avr/io.h>
#include <avr/interrupt.h>

#define BTO 7
#define LED_B 12
#define LED_G 11


void setup() {
  pinMode(LED_B, OUTPUT);  
  pinMode(LED_G, OUTPUT);  
  pinMode(BTO, INPUT_PULLUP);

  cli(); // disable global interrupts

  TCCR1A = 0; // clear TCCR1A
  TCCR1B = 0; // clear TCCR1B

  TIMSK1 = (1 << TOIE1); // enable overflow interrupt
  TCCR1B |= (1 << CS12); // set prescale to F_CPU/256

  sei(); // enable global interrupts
}

bool status_led = false;
bool status_led_g = false;

void loop() {
  	
  digitalWrite(LED_B, status_led);   

	status_led = !status_led;

	while(!digitalRead(BTO)){
		delay(100);
	}

	delay(500);
}

ISR(TIMER1_OVF_vect) {
	status_led_g = !status_led_g;
	digitalWrite(LED_G,status_led_g);
}
