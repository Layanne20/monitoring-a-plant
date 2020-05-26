#include <DHT.h>
#include <DHT_U.h>

#define pino_sinal_analogico A0    // sensor de umidade do solo
#define pino_led_vermelho 5    // solo seco
#define pino_led_amarelo 6    // solo com umidade moderada
#define pino_led_verde 7     // solo úmido
 
int valor_analogico;

//const int pinoLed = 4; //PINO DIGITAL UTILIZADO PELO LED
//const int pinoLDR = A5; //PINO ANALÓGICO UTILIZADO PELO LDR
 
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // Tipo do sensor
#define tempo 2000    // Intervalo de tempo de cada leitura
#define tempoLDR 21600000    // Tempo de exposição ao Sol 

unsigned long delay1 = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  pinMode(pino_sinal_analogico, INPUT);
  pinMode(pino_led_vermelho, OUTPUT);
  pinMode(pino_led_amarelo, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);

// Sensor LDR

  //pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  //pinMode(pinoLDR, INPUT); //DEFINE O PINO COMO ENTRADA
 

// Sensor DTH11

// pinMode(pinSensorD, INPUT);
  dht.begin();
}

void apagaleds()
{
  digitalWrite(pino_led_vermelho, LOW);
  digitalWrite(pino_led_amarelo, LOW);
  digitalWrite(pino_led_verde, LOW);
}
 
void loop()
{
  //Le o valor do pino A0 do sensor
  valor_analogico = analogRead(pino_sinal_analogico);
 
  //Mostra o valor da porta analogica no serial monitor
  Serial.print("Porta analogica: ");
  Serial.print(valor_analogico);
 
  //Solo umido, acende o led verde
  if (valor_analogico > 0 && valor_analogico < 400)
  {
    Serial.println(" Status: Solo umido");
    apagaleds();
    digitalWrite(pino_led_verde, HIGH);
  }
 
  //Solo com umidade moderada, acende led amarelo
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    Serial.println(" Status: Umidade moderada");
    apagaleds();
    digitalWrite(pino_led_amarelo, HIGH);
  }
 
  //Solo seco, acende led vermelho
  if (valor_analogico > 800 && valor_analogico < 1024)
  {
    Serial.println(" Status: Solo seco");
    apagaleds();
    digitalWrite(pino_led_vermelho, HIGH);
  }
  delay(100);


// Sensor LDR

  //O VALOR 600 PODE SER AJUSTADO
  //if(analogRead(pinoLDR) > 600){ //SE O VALOR LIDO FOR MAIOR QUE 600, FAZ
    //digitalWrite(pinoLed, HIGH); //ACENDE O LED
 // }   
  //else{ //SENÃO, FAZ
    //digitalWrite(pinoLed, LOW); //APAGA O LED
  //}  


// Sensor DTH11

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falha na leitura do sensor DHT!"));
    return;
  }
  if((millis() - delay1) >= tempo){
    
  Serial.print(F("   Umidade do ar: "));
  Serial.print(h);
  Serial.print(F("%   Temperatura: "));
  Serial.print(t);
  Serial.println(F("°C "));

  delay1 = millis();
}
}
