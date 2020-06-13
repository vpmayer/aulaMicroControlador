#include <avr/io.h>
#include <avr/interrupt.h>
#include <SPI.h>

#define SS 10

volatile int pessoa = 0;

void setup() {
  Serial.begin(9600);
	
  //Setup SPI Master
  SPI.begin ();
  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);  // ensure SS stays high for now

}


void loop() {
  byte c;
	if(++pessoa>99)
    pessoa = 0;

	delay(250);
  digitalWrite(SS, LOW);
  delay(250);
  c = SPI.transfer((char)pessoa);
  delay(250);
  digitalWrite(SS, HIGH);
  delay(250);

  Serial.println(pessoa);
}
