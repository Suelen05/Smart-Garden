#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ds1302.h>
#include <TimeLib.h>

//Definições dos pinos
#define DHTPIN 2
#define DHTTYPE DHT22
#define SOLO_PIN A2
#define LUZ_PIN A1
#define LED_VERDE 6
#define LED_VERMELHO 7

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int CE_PIN = 4;
const int IO_PIN = 5;
const int SCLK_PIN = 3;

Ds1302 rtc(5, 3, 4);

// Variáveis globais dos sensores
float temperatura = 0;
float umidadeAr = 0;
int umidadeSolo = 0;
int luz = 0;
Ds1302::DateTime dataHora;

void setup() {

  Serial.begin(9600);
  dht.begin();
  rtc.init();

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("Smart Garden");

  delay(2000);

}

void loop() {

  lerSensores();
  controlarLED();
  exibirLeiturasLCD();
  exibirAlertasLCD();
  imprimirSerial();

  delay(2000);

}

//Leitura dos Sensores
void lerSensores() {

  temperatura = dht.readTemperature();
  umidadeAr = dht.readHumidity();
  umidadeSolo = analogRead(SOLO_PIN);
  luz = analogRead(LUZ_PIN);
  rtc.getDateTime(&dataHora);

}

//Controle dos LEDs
void controlarLED() {

  bool soloSeco = (umidadeSolo > 700);

  if (soloSeco) {

    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);

  } else {

    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);

  }

}

// Exibir os valores no LCD
void exibirLeiturasLCD() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura);
  lcd.print("C U:");
  lcd.print(umidadeAr);

  lcd.setCursor(0, 1);
  lcd.print("Solo:");
  lcd.print(umidadeSolo);
  lcd.print(" Luz:");
  lcd.print(luz);

  delay(3000);

}

//Exibir alertas no LCD 
void exibirAlertasLCD() {

  bool ehNoite = (dataHora.hour >= 18 || dataHora.hour < 6);

  if (temperatura > 30) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Alerta:");

    lcd.setCursor(0, 1);
    lcd.print("Temp Alta!");

    Serial.println("ALERTA: Temperatura Alta!");

    delay(2000);

  }

  if (umidadeAr < 30) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Alerta:");

    lcd.setCursor(0, 1);
    lcd.print("Ar Seco!");

    Serial.println("ALERTA: Umidade do Ar muito baixa!");

    delay(2000);

  }

  if (!ehNoite && luz < 200) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Alerta:");

    lcd.setCursor(0, 1);
    lcd.print("Pouca Luz!");

    Serial.println("ALERTA: Baixa Luminosidade!");

    delay(2000);

  }
}

//Exibir os valores no Serial Monitor
void imprimirSerial() {

  Serial.print("Data: 20");
  Serial.print(dataHora.year);
  Serial.print("/");
  Serial.print(dataHora.month);
  Serial.print("/");
  Serial.print(dataHora.day);
  Serial.print(" Hora: ");
  Serial.print(dataHora.hour);
  Serial.print(":");
  Serial.print(dataHora.minute);
  Serial.print(":");
  Serial.println(dataHora.second);

  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Umidade do ar: ");
  Serial.println(umidadeAr);
  Serial.print("Umidade do solo: ");
  Serial.println(umidadeSolo);
  Serial.print("Luz: ");
  Serial.println(luz);
  Serial.println("-----------------------");
}
