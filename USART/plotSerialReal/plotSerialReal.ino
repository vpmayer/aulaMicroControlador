#define SETPOINT_PIN A5
#define PV_PIN A4
#define OUTPUT_PIN 11


void msgPrint(int setpoint, int manipulated);

char serialRX;
String mydata;
int i = 0;
int setpoint = 0;
int manipulated = 0;
int processVariable = 0;

void setup() {
  Serial.begin(115200);

  pinMode(SETPOINT_PIN, INPUT);
  pinMode(PV_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  Serial.print("SP:");
  Serial.print(",");
  Serial.print("PV:");
  Serial.print(",");
  Serial.print("error:");
  Serial.println(" ");
}

void loop() {

  while (Serial.available() > 0) {


    serialRX = Serial.read();
    mydata += serialRX;
    i++;
    // Serial.println(serialRX);
    if(serialRX == '#'){
      i=0;
      mydata = "";
    }
    if(i>=3){
      setpoint = mydata.toInt();
      mydata = "";
      i=0;
    }
  }
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
