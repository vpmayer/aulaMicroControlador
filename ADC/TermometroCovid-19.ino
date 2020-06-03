#define LED_R 13
#define LED_Y 12
#define LED_G 11
#define TMP_PIN	A0

float temp = 0.0;
int tmp_digtal = 0;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);

  pinMode(TMP_PIN, INPUT);
  analogReference(DEFAULT);
}

float convertTmp(int tmp);

void loop() {

	tmp_digtal = analogRead(TMP_PIN);

	temp = convertTmp(tmp_digtal);


	if(temp < 37.0){
		digitalWrite(LED_G, HIGH);
		digitalWrite(LED_Y, LOW);
		digitalWrite(LED_R, LOW);
	} else{
		if (temp <= 38.0){
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_Y, HIGH);
			digitalWrite(LED_R, LOW);
		} else{
			digitalWrite(LED_G, LOW);
			digitalWrite(LED_Y, LOW);
			digitalWrite(LED_R, HIGH);
		}
	}  

	delay(500);                  
}

float convertTmp(int tmp){
	float V;
	float graus;
	float Vref = 5.0;
	//tmp = 25.0 = 0.75V
	// Delta = 10 mV/°C
	// t(v) = (V/0.01) - 50
	

	// adc = (Vin * 1024)/ Vref
	// Vin = (adc*Vref)/1024
	V = (float)tmp; 
	V = (V * Vref);
	V = V/1024.0;

	graus = (V/0.01);
	graus = graus - 50.0;

	return graus;
}
