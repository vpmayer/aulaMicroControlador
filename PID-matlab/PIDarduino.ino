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
double kp=4.0F;
double ki=1.0F;
double kd=0.001F;

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
  processVariable = map(analogRead(PV_PIN),0,1023,0,1000);
  Input = processVariable;

  // manipulated = map(setpoint,0,100,0,255);
  
  msgPrint(setpoint, Output, processVariable);

  Output = map(Output,0,1000,0,255);
  Output = constrain(Output,0,255);
  analogWrite(OUTPUT_PIN, Output);
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
  error = setpoint - manipulated;
  Serial.print(error);
  Serial.println(" ");
}

void Compute(){
  unsigned long now = millis();
  double timeChange = (double)(now - lastTime); //time interval
  timeChange /= 1000.0F;
  double error = Setpoint - Input; //erro 
  errSum += (error * timeChange); // somatoria do erro (integral do erro)
  double dErr = (error - lastErr) / timeChange; //diferença do erro (derivada do erro)  
  Output = kp * error + ki * errSum + kd * dErr; 
  // Saida = ganho Direto + ganho itegral * integral do erro + ganho derivada + derivada do erro
  lastErr = error; //atualiza o erro
  lastTime = now; //atualiza o ultimo tempo
}