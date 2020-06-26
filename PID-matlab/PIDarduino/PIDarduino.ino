#define SETPOINT_PIN A5
#define PV_PIN A4
#define OUTPUT_PIN 11


void msgPrint(int setpoint, int manipulated, int PV);

char serialRX;
String mydata;
int i = 0;
int setpoint = 0;
int manipulated = 0;
int processVariable = 0;

unsigned long lastTime;
double Input, Output, Setpoint;
double errSum, lastErr;
double kp=4.0;
double ki=1.0;
double kd=0;

void setup() {
  Serial.begin(115200);

  pinMode(SETPOINT_PIN, INPUT);
  pinMode(PV_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  Serial.print("SP:");
  Serial.print(",");
  Serial.print("MV:");
  Serial.print(",");
  Serial.print("PV:");
  Serial.print(",");
  Serial.print("error:");
  Serial.println(" ");
}

void loop() {

  if (Serial.available() > 0) {


    serialRX = Serial.read();
    mydata += serialRX;
    i++;
    // Serial.println(serialRX);
    if(serialRX == '#')
      mydata = "";
    if(i>=3){
      setpoint = mydata.toInt();
      Setpoint = setpoint;
      mydata = "";
      i=0;
    }

  }
  processVariable = map(analogRead(PV_PIN),0,1023,0,100);
  Input = processVariable;

  // manipulated = map(setpoint,0,100,0,255);

  Output = constrain(Output,0,255);
  analogWrite(OUTPUT_PIN, Output);
  msgPrint(setpoint, Output, processVariable);
  Compute();
  delay(100);
}

void msgPrint(int setpoint, int manipulated,int PV){
  int error;
  // Serial.print("SP:");
  Serial.print(setpoint);
  Serial.print(",");
  // Serial.print("MV:");
  Serial.print(manipulated);
  Serial.print(",");
  // Serial.print("PV:");
  Serial.print(PV);
  Serial.print(",");
  // Serial.print("error:");
  error = setpoint - PV;
  Serial.print(error);
  Serial.println(" ");
}

void Compute(){
  unsigned long now = millis();
  double timeChange = (double)(now - lastTime);
  timeChange /= 100.0;
  double error = Setpoint - Input;
  errSum += (error * timeChange);
  double dErr = (error - lastErr) / timeChange;
  Output = kp * error + ki * errSum + kd * dErr;
  lastErr = error;
  lastTime = now;
}