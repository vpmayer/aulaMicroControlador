#define RED 13
#define BLUE 12
#define GREEN 11
#define BTO 7

char serialRX = 0;

void setup() {
	
  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BTO, INPUT_PULLUP);

}


void loop() {
 
  if (Serial.available() > 0) {

    Serial.print("Recebi um ");
    serialRX = Serial.read();
    Serial.println(serialRX);
    delay(1000);
  }

  switch(serialRX){

    case 'R':
      digitalWrite(RED,HIGH);
      digitalWrite(BLUE,LOW);
      digitalWrite(GREEN,LOW);
      serialRX = 0;
      break;
    case 'G':
      digitalWrite(RED,LOW);
      digitalWrite(BLUE,LOW);
      digitalWrite(GREEN,HIGH);
      serialRX = 0;
      break;
    case 'B':
      digitalWrite(RED,LOW);
      digitalWrite(BLUE,HIGH);
      digitalWrite(GREEN,LOW);
      serialRX = 0;
      break;
    case 0:
      Serial.print("Botao: ");
      Serial.println(digitalRead(BTO));
      break;
    default:
      Serial.println("Comando não reconhecido.");
      Serial.println("Digite R, G ou B");
      break;
  }

  if(!digitalRead(BTO)){
    digitalWrite(RED,LOW);
    digitalWrite(BLUE,LOW);
    digitalWrite(GREEN,LOW);
  }

  delay(250);

}
