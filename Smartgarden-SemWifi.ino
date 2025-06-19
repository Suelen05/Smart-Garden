#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ds1302.h>
#include <TimeLib.h>

// --- Definições de pinos ---
#define DHTPIN 2
#define DHTTYPE DHT22
#define SOLO_PIN A2
#define LUZ_PIN A1
#define LED_VERDE 6
#define LED_VERMELHO 7

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RTC DS1302
const int CE_PIN = 4;
const int IO_PIN = 5;
const int SCLK_PIN = 3;
Ds1302 rtc(5, 3, 4);

void setup() {
  Serial.begin(9600);  //print
  dht.begin();
  rtc.init();
  // Estrutura para data e hora
  Ds1302::DateTime dt;

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("Smart Garden");
  delay(2000);
}

void loop() {
  // Ler sensores
  float temperatura = dht.readTemperature();
  float umidadeAr = dht.readHumidity();
  int umidadeSolo = analogRead(SOLO_PIN);
  int luz = analogRead(LUZ_PIN);

  // Ler e exibir a hora no Serial Monitor
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  Serial.print("Data: 20");
  Serial.print(now.year);
  Serial.print("/");
  Serial.print(now.month);
  Serial.print("/");
  Serial.print(now.day);

  Serial.print(" Hora: ");
  Serial.print(now.hour);
  Serial.print(":");
  Serial.print(now.minute);
  Serial.print(":");
  Serial.println(now.second);

  // Lógica para alerta de solo seco
  bool soloSeco = umidadeSolo > 700;

  if (soloSeco) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  } else {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
  }

  // Exibir no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura);
  lcd.print(" U:");
  lcd.print(umidadeAr);

  lcd.setCursor(0, 1);
  lcd.print("Solo:");
  lcd.print(umidadeSolo);
  lcd.print(" Luz:");
  lcd.print(luz);

  // Debug no Serial Monitor
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Umidade do ar: ");
  Serial.println(umidadeAr);
  Serial.print("Umidade do solo: ");
  Serial.println(umidadeSolo);
  Serial.print("Luz: ");
  Serial.println(luz);
  Serial.println("-----------------------");

  delay(5000);  // Aguarda 5 segundos antes da próxima leitura
}
