#include <avr/io.h>
#include <avr/interrupt.h>

#define SETPOINT_PIN A5
#define PV_PIN A4
#define OUTPUT_PIN 11

#define TimerLoader 45535 // calculo dentro do setupTimer1
#define LoopCont 35
int setpoint = 0;
int manipulated = 0;
int processVariable = 0;

unsigned long lastTime;

double Input, Output, Setpoint;
double errSum, lastErr, lastOutput;
double kp=4.0F;
double ki=1.0F;
double kd=0.0F;

double ganhos[3];
double errors[3];
double MV[2];

void initPIDvalues();

void msgPrint(int setpoint, int manipulated,int PV);
void setupPIDpins(int pvPin, int mvPin, int spPin);
void readPorcessValues();
void ComputePIDloop();
void writePIDOut();
void setSetPoint(int setpoint);


void setupPIDTimer1();
void computePIDTimer1();
void setupPIDTmr1Gains(double kp, double ki, double kd);


void setup() {
  Serial.begin(115200);

  setupPIDpins(PV_PIN, OUTPUT_PIN, SETPOINT_PIN);

  Serial.print("SP:");
  Serial.print(",");
  Serial.print("MV:");
  Serial.print(",");
  Serial.print("PV:");
  Serial.print(",");
  Serial.print("error:");
  Serial.println(" ");

  initPIDvalues();
  disablePIDTmr1();
  setupPIDTimer1();
  disablePIDTmr1();
  delay(2000);
}

void loop() {

  kp = 4.0F;
  ki = 1.0F;
  setSetPoint(300);

  for(int i=0; i<LoopCont ; i++){
    readPorcessValues();
    ComputePIDloop();
    writePIDOut();
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }
  setSetPoint(400);
  for(int i=0; i<LoopCont ; i++){
    readPorcessValues();
    ComputePIDloop();
    writePIDOut();
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }
  setSetPoint(300);
  for(int i=0; i<LoopCont ; i++){
    readPorcessValues();
    ComputePIDloop();
    writePIDOut();
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }

  kp = 8.0F; 
  ki = 1.0F;
  for(int i=0; i<LoopCont ; i++){
    readPorcessValues();
    ComputePIDloop();
    writePIDOut();
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }
  setSetPoint(400);
  for(int i=0; i<LoopCont ; i++){
    readPorcessValues();
    ComputePIDloop();
    writePIDOut();
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }
  setSetPoint(300);
  for(int i=0; i<LoopCont ; i++){
    readPorcessValues();
    ComputePIDloop();
    writePIDOut();
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }

  kp = 4.0F;
  ki = 1.0F;
  setupPIDTmr1Gains(kp,ki,kd);
  setSetPoint(300);
  enablePIDTmr1();
  for(int i=0; i<LoopCont ; i++){
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }
  setSetPoint(400);
  enablePIDTmr1();
  for(int i=0; i<LoopCont ; i++){
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }
  setSetPoint(300);
  enablePIDTmr1();
  for(int i=0; i<LoopCont ; i++){
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }

  kp = 8.00F;
  ki = 1.0F;
  setupPIDTmr1Gains(kp,ki,kd);
  setSetPoint(300);
  for(int i=0; i<LoopCont ; i++){
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }
  setSetPoint(400);
  enablePIDTmr1();
  for(int i=0; i<LoopCont ; i++){
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }
  setSetPoint(300);
  enablePIDTmr1();
  for(int i=0; i<LoopCont ; i++){
    msgPrint(Setpoint, Output, processVariable);
    delay(100);
  }

  disablePIDTmr1();
}


int _pvPin,_mvPin,_spPin;

void initPIDvalues(){
  setpoint = 0;
  manipulated = 0;
  processVariable = 0;

  lastTime = 0;

  Input = 0;
  Output = 0;
  Setpoint = 0;
  errSum = 0;
  lastErr = 0;
  lastOutput = 0;
  kp=4.0F;
  ki=1.0F;
  kd=0.0F;
}

void msgPrint(int setpoint, int manipulated,int PV){
  int error;
  int auxManip = map(manipulated,0,255,0,1000);
  // Serial.print("SP:");
  Serial.print(setpoint);
  Serial.print(",");
  // Serial.print("MV:");
  // Serial.print(0);
  Serial.print(auxManip);
  Serial.print(",");
  // Serial.print("PV:");
  Serial.print(PV);
  Serial.print(",");
  // Serial.print("error:");
  error = setpoint - auxManip;
  // Serial.print(0);
  Serial.print(error + setpoint);
  Serial.println(" ");
}


void setupPIDpins(int pvPin, int mvPin, int spPin){
  pinMode(spPin, INPUT);
  pinMode(pvPin, INPUT);
  pinMode(mvPin, OUTPUT);
  _spPin = spPin;
  _mvPin = mvPin;
  _pvPin = pvPin;
}

void readPorcessValues(){
  processVariable = map(analogRead(_pvPin),0,1023,0,1000);
  Input = (double)processVariable;
}

void ComputePIDloop(){

  unsigned long now = millis();
  double timeSample = (double)(now - lastTime); //time interval
  timeSample /= 1000.0F;
  lastOutput = Output; // salva o ultimo erro para adicionar no valor da saida
  double error = Setpoint - Input; //erro 
  errSum += (error * timeSample); // somatoria do erro (integral do erro)
  double dErr = (error - lastErr) / timeSample; //diferença do erro (derivada do erro)  
  Output = (lastOutput) +  ((kp * error) + (ki * errSum) + (kd * dErr)); 
  // Saida = ganho Direto + ganho itegral * integral do erro + ganho derivada + derivada do erro
  Output = map(Output,0,1000,0,255);
  Output = constrain(Output,0,255);

  lastErr = error; //atualiza o erro
  lastTime = now; //atualiza o ultimo tempo
}

void writePIDOut(){
  
  analogWrite(_mvPin, Output); //escreve o valor na saida.
}

void setSetPoint(int setpoint){
  
  Setpoint = setpoint;
}

// PID TIMER

void setupPIDTimer1(){
  //carregar o timer para rodar a cada 10ms
  /*
    F_CPU = 16.000.000 -> prescale = 8
    16000000/8 -> fTimer1 = 2.000.000 hz
    peridoTimer1 = 1/fTimer -> 0,0000005 segundos
    Periodo desejado = 0.01;
    contador = perido desejado / periodoTimer1
    contador = 0.01/0.0000005 -> contador = 20000
    diferença para overflow do timer de 16bits
    65535 - contador

    TimerLoader = 65535 - 20000 = 45535
    TimerLoader = 45535; 
  */

  cli(); // disable global interrupts

  TCCR1A = 0; // clear TCCR1A
  TCCR1B = 0; // clear TCCR1B

  // TIMSK1 = (1 << TOIE1); // enable overflow interrupt
  TCCR1B |= (1 << CS10); // set prescale to F_CPU/8
  TCNT1 = TimerLoader; // pre load timer counter

  sei(); // enable global interrupts
}
void enablePIDTmr1(){

  cli(); // disable global interrupts
  TIMSK1 = (1 << TOIE1); // enable overflow interrupt
  sei(); // enable global interrupts
}
void disablePIDTmr1(){

  cli(); // disable global interrupts
  TIMSK1 &= ~(1 << TOIE1); // enable overflow interrupt
  sei(); // enable global interrupts
}

void computePIDTimer1(){

  MV[1] = MV[0];
  errors[2]=errors[1];
  errors[1]=errors[0];
  errors[0]= (double)(Setpoint - Input);

  MV[0] = MV[1]; 
  MV[0] += (errors[0]*ganhos[0]);
  MV[0] += (errors[1]*ganhos[1]);
  MV[0] += (errors[2]*ganhos[2]);

/*  if(MV[0]>1000.0F)
    MV[0] = 1000.0F;
  if(MV[0]<0)
    MV[0]=0.0F;*/

  Output = MV[0];

  Output = map(Output,0,1000,0,255);
  Output = constrain(Output,0,255);
}

void setupPIDTmr1Gains(double kp, double ki, double kd){
  const double Tsample = 0.01F; // define valor como ponto flutuante;
  
  ganhos[0] = kp + ((ki*Tsample)/2.0F) + (kd/Tsample);

  ganhos[1] = -kp + ((ki*Tsample)/2.0F) - ((2.0F*kd)/Tsample);

  ganhos[2] = kd/Tsample;

  for(int i=0;i<3;i++){
    errors[i]=0;
  }
  for(int i=0;i<2;i++){
    MV[i]=0;
  }
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = TimerLoader; 

  readPorcessValues();
  
  computePIDTimer1();

  writePIDOut();
}