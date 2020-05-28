void setup() {
  //inicializa o pino 13 do arduino como saída digital
  pinMode(13, OUTPUT); 

}

//prototipos de funções
void traco();
void ponto();
void SOS();


void loop() {

  SOS();

}

void traco(){
  digitalWrite(13, HIGH);   
  delay(750);                       
  digitalWrite(13, LOW);    
  delay(250);
}

void ponto(){
  digitalWrite(13, HIGH);   
  delay(250);                       
  digitalWrite(13, LOW);    
  delay(250);
}

void SOS(){
  uint8_t i=0;

  for(i=0;i<3;i++){
    ponto();
  }
  for(i=0;i<3;i++){
    traco();
  }
  for(i=0;i<3;i++){
    ponto();
  }

  delay(750);
}