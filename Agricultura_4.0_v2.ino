#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

String mensagem;

#define pinSensor A0    // Sensor de umidade do solo
 
int val;

float t;

const int pinoLDR = A5; //Pino analógico utilizado pelo LDR
 
#define DHTPIN A5     // Pino analógico utilizado pelo sensor DTH
#define DHTTYPE DHT11   // Tipo do sensor

DHT dht(DHTPIN, DHTTYPE);

// Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Cria outro smile :)
byte smile1[8] = {
 B00000,
 B00000,
 B01010,
 B01010,
 B00000,
 B10001,
 B11111,
 B00000,
};
 
// Cria outro smile :/
byte smile2[8] = {
 B00000,
 B00000,
 B01010,
 B01010,
 B00000,
 B00000,
 B11111,
 B00000,
};
 
// Cria outro smile :(
byte smile3[8] = {
 B00000,
 B00000,
 B01010,
 B01010,
 B00000,
 B11111,
 B10001,
 B00000,
};

// Array simbolo grau
byte grau[8] = { 
  B00001100,
  B00010010,
  B00010010,
  B00001100,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};
void setup() {
  
Serial.begin(9600); // Inicializa a serial
lcd.begin(16,2); // Inicializa LCD
lcd.clear(); // Limpa o LCD
// Cria o caractere customizado com o simbolo do grau e os smiles
lcd.createChar(0, grau);
lcd.createChar(1, smile1); 
lcd.createChar(2, smile2);
lcd.createChar(3, smile3);
}

void loop() {
  
// Sensor DTH11
t = dht.readTemperature(); // Lê o valor da temperatura
lcd.setCursor(0,2);
lcd.print("Temp : ");
lcd.print(" ");
lcd.setCursor(7,2);
lcd.print(t,0);
lcd.setCursor(12,2);
 
// Mostra o simbolo do grau formado pelo array
lcd.write((byte)0);

// Intervalo recomendado para leitura do sensor
delay(2000);

// Sensor de umidade do solo
//Lê o valor do pino do sensor
 val = analogRead(pinSensor);

// Mostrando o valor lido na serial do arduino
 Serial.print("Valor lido pelo sensor: ");
 Serial.println(val);
 
 // Umidade alta, imprime isso no display
 if (val > 0 && val < 400)
 {
 lcd.setCursor(4,0);
 lcd.print("Solo umido");
 lcd.setCursor(13,2);
 lcd.write(1);
 }
 // Umidade moderada, imprime isso no display
 if (val > 400 && val < 800)
 {
 lcd.setCursor(0,0);
 lcd.print("Umidade moderada");
 lcd.setCursor(13,2);
 lcd.write(2);
 }
 // Umidade baixa, imprime isso no display
 if (val > 800 && val < 1024)
 {
 lcd.setCursor(4,0);
 lcd.print("Solo seco");
 lcd.setCursor(13,2);
 lcd.write(3);
 }
 
 delay(2000); // Delay para reiniciar outra leitura
 lcd.clear(); // Apaga o que está escrito no display
}
