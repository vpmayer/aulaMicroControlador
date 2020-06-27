#include <avr/io.h>
#include <avr/interrupt.h>

#define SETPOINT_PIN A5
#define PV_PIN A4
#define OUTPUT_PIN 11

#define TimerLoader 45535 // calculo dentro do setupTimer1()

void msgPrint(int setpoint, int manipulated, int PV);
void setupTimer1();

char serialRX;
String mydata;
int i = 0;
int setpoint = 0;
int manipulated = 0;
int processVariable = 0;

unsigned long lastTime;

double Input, Output, Setpoint;
double errSum, lastErr, lastOutput;
double kp=4.0F;
double ki=1.0F;
double kd=0.0F;

void setup() {
  Serial.begin(115200);

  pinMode(SETPOINT_PIN, INPUT);
  pinMode(PV_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  setupTimer1();

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
  
  msgPrint(setpoint, Output, processVariable);
  delay(100);
}

void msgPrint(int setpoint, int manipulated,int PV){
  int error;
  // Serial.print("SP:");
  Serial.print(setpoint);
  Serial.print(",");
  // Serial.print("MV:");
  // Serial.print(0);
  Serial.print(manipulated);
  Serial.print(",");
  // Serial.print("PV:");
  Serial.print(PV);
  Serial.print(",");
  // Serial.print("error:");
  error = setpoint - manipulated;
  // Serial.print(0);
  Serial.print(error);
  Serial.println(" ");
}

void Compute(){
  unsigned long now = millis();
  double timeSample = (double)(now - lastTime); //time interval
  timeSample /= 1000.0F;
  lastOutput = Output; // salva o ultimo erro para adicionar no valor da saida
  double error = Setpoint - Input; //erro 
  errSum += (error * timeSample); // somatoria do erro (integral do erro)
  double dErr = (error - lastErr) / timeSample; //diferença do erro (derivada do erro)  
  Output = (lastOutput) +  ((kp * error) + (ki * errSum) + (kd * dErr)); 
  // Saida = ganho Direto + ganho itegral * integral do erro + ganho derivada + derivada do erro
  lastErr = error; //atualiza o erro
  lastTime = now; //atualiza o ultimo tempo
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

ISR(TIMER1_OVF_vect) {
  TCNT1 = TimerLoader; 

  processVariable = map(analogRead(PV_PIN),0,1023,0,1000);
  Input = processVariable;

  // manipulated = map(setpoint,0,100,0,255);
  


  Output = map(Output,0,1000,0,255);
  Output = constrain(Output,0,255);
  analogWrite(OUTPUT_PIN, Output);
  Compute();
}