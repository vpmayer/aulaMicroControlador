#define PUT_PIN 3

int brightness = 0; // how bright the LED is
int fadeAmount = 5; // how many points to fade

void setup()
{
  pinMode(PUT_PIN, OUTPUT);
}

void loop()
{
  analogWrite(PUT_PIN, brightness);
  brightness = brightness + fadeAmount;
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
    delay(1000);
  }
  delay(100);
}
