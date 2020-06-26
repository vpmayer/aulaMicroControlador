#include <avr/io.h>
#include <avr/interrupt.h>

#define PV_PIN A4
#define OUTPUT_PIN 11
#define TimerLoader 45535 // calculo dentro do setupTimer1()

double ganhos[3];
double errors[3];
double MV[2];
double PVariable;
double Setpoint;

double kp=4.0F;
double ki=1.0F;
double kd=0.0F;

void msgPrint(int setpoint, int manipulated, int processVariable);
void setupTimer1();
void setupPID(double kp, double ki, double kd);
void ComputePID();

char serialRX;
String mydata;
int i = 0;
int setpoint = 0;
int manipulated = 0;


void setup() {
  Serial.begin(115200);

  pinMode(PV_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  setupPID(kp,ki,kd);

  setupTimer1(); //setup da interrupção por overflow timer1;

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
      Setpoint = (double)setpoint;
      mydata = "";
      i=0;
    }

  }
  
  msgPrint((int)Setpoint,(int)MV[0],(int)PVariable);
  delay(100);
}

void msgPrint(int setpoint, int manipulated,int processVariable){
  int error;
  // Serial.print("SP:");
  Serial.print(setpoint);
  Serial.print(",");
  // Serial.print("MV:");
  Serial.print(manipulated);
  Serial.print(",");
  // Serial.print("PV:");
  Serial.print(processVariable);
  Serial.print(",");
  // Serial.print("error:");
  error = setpoint - manipulated;
  Serial.print(error);
  Serial.println(" ");
}

void computePID(){
  PVariable = map(analogRead(PV_PIN),0,1023,0,1000);

  MV[1] = MV[0];
  errors[2]=errors[1];
  errors[1]=errors[0];
  errors[0]= (double)(Setpoint - PVariable);

  MV[0] = MV[1]; 
  MV[0] += (errors[0]*ganhos[0]);
  MV[0] += (errors[1]*ganhos[1]);
  MV[0] += (errors[2]*ganhos[2]);

  if(MV[0]>1000.0F)
    MV[0] = 1000.0F;
  if(MV[0]<0)
    MV[0]=0.0F;

  manipulated = map(MV[0],0,1000,0,255);
  analogWrite(OUTPUT_PIN,manipulated);
}

void setupTimer1(){
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

  TIMSK1 = (1 << TOIE1); // enable overflow interrupt
  TCCR1B |= (1 << CS10); // set prescale to F_CPU/8
  TCNT1 = TimerLoader; // pre load timer counter

  sei(); // enable global interrupts
}


void setupPID(double kp, double ki, double kd){
  const double Tsample = 0.01F; // define valor como ponto flutuante;
  
  ganhos[0] = kp + ((ki*Tsample)/2.0F) + (kd/Tsample);

  ganhos[1] = -kp + ((ki*Tsample)/2.0F) - ((2.0F*kd)/Tsample);

  ganhos[2] = kd/Tsample;

  // ganhos[0] = kp + ((ki)/2.0F) + (kd);

  // ganhos[1] = -kp + ((ki)/2.0F) - ((2.0F*kd));

  // ganhos[2] = kd;

  for(int i=0;i<3;i++){
    errors[i]=0;
  }
  for(int i=0;i<2;i++){
    MV[i]=0;
  }
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = TimerLoader; 

  computePID();
}