#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>


volatile int pessoa = 0;

void setup() {
	
  Wire.begin(); // join i2c bus (address optional for master)  

}


void loop() {
  byte c;
	if(++pessoa>99)
    pessoa = 0;

	Wire.beginTransmission(4); // transmit to device #4
  Wire.write(pessoa);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

  delay(1000);

}
