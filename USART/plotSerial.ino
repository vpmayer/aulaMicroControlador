#define SETPOINT_PIN A5
#define PV_PIN A4
#define OUTPUT_PIN 11


void msgPrint(int setpoint, int manipulated);

int setpoint = 0;
int manipulated = 0;
int processVariable = 0;

void setup() {
  Serial.begin(9600);

  pinMode(SETPOINT_PIN, INPUT);
  pinMode(PV_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  Serial.print("SP:");
  Serial.print(",");
  Serial.print("MV:");
  Serial.print(",");
  Serial.print("error:");
  Serial.println(" ");
}

void loop() {
  setpoint = map(analogRead(SETPOINT_PIN),0,1023,0,100);
  processVariable = map(analogRead(PV_PIN),0,1023,0,100);
  manipulated = map(setpoint,0,100,0,255);
  analogWrite(OUTPUT_PIN, manipulated);
  msgPrint(setpoint, processVariable);
  delay(100);
}

void msgPrint(int setpoint, int manipulated){
  int error;
  // Serial.print("SP:");
  Serial.print(setpoint);
  Serial.print(",");
  // Serial.print("MV:");
  Serial.print(manipulated);
  Serial.print(",");
  // Serial.print("error:");
  error = setpoint - manipulated;
  Serial.print(error);
  Serial.println(" ");
}
