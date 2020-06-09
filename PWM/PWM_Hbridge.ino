#define PUT_PIN 9
#define DIRECTION 8

int speed = 0; // how bright the LED is
int step = 5; // how many points to fade

void setup()
{
  pinMode(PUT_PIN, OUTPUT);
  pinMode(DIRECTION, OUTPUT);
}

void loop()
{
  analogWrite(PUT_PIN, speed);
  speed = speed + step;
  if (speed == 0 || speed == 255) {
    step = -step ;
    if(speed == 0)
      digitalWrite(DIRECTION,!digitalRead(DIRECTION));
    delay(1000);
  }
  delay(100);
}
