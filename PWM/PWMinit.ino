#define PWM_PIN 3


byte duty = 127;

void setup() {
  pinMode(PWM_PIN, OUTPUT);

  analogWrite(PWM_PIN,duty);
}

void loop() {

  delay(500);
}
