# Smart Garden 🌱 - Sistema de Monitoramento Inteligente para Plantas Domésticas

Este é um projeto de IoT desenvolvido para monitorar em tempo real as condições ambientais de plantas em vasos pequenos, utilizando sensores conectados a um microcontrolador Arduino Uno e enviando os dados para a nuvem via módulo ESP8266.

---

## 📊 Objetivo
Fornecer um sistema acessível e replicável para o monitoramento de:
- Temperatura e umidade do ar
- Umidade do solo
- Luminosidade
- pH do solo
- Data e hora das leituras

---

## 🫠 Componentes Utilizados

### Hardware
- Arduino Uno SMD R3
- Sensor DHT22 (temperatura e umidade do ar)
- Sensor capacitivo de umidade do solo
- Sensor de pH com sonda
- LDR com resistor de 10kΩ (ou BH1750)
- RTC DS1302
- Display LCD 16x2 com módulo I2C
- LEDs (verde e vermelho)
- Módulo ESP8266 ESP-01
- Conversor de nível lógico (5V para 3.3V)
- Protoboard, jumpers, fonte 5V

### Software
- Arduino IDE
- Bibliotecas: `DHT.h`, `Wire.h`, `LiquidCrystal_I2C.h`, `DS1302RTC.h`, `TimeLib.h`, `SoftwareSerial.h`
- Plataforma ThingSpeak para visualização remota
- Protocolo HTTP para envio de dados via ESP-01

---

## 🔄 Funcionamento
1. Os sensores conectados ao Arduino realizam leituras periódicas.
2. Os dados são exibidos em tempo real no LCD e também via Serial.
3. O RTC DS1302 registra a data e hora das leituras.
4. LEDs indicam o estado de alerta da planta (solo seco, etc).
5. O módulo ESP8266 transmite os dados para a nuvem (ThingSpeak).
6. Um dashboard exibe gráficos e histórico dos dados.

---

## 🎨 Dashboard
- Acesse: [ThingSpeak](https://thingspeak.com/)
- Crie um canal com os campos: temperatura, umidade do ar, umidade do solo, pH, luz
- Adicione widgets como: line charts, gauges, displays

---

## ✨ Futuras Expansões
- Acionamento automático de bomba de água
- Notificações por e-mail ou Telegram
- Integração com Google Sheets ou App Android
- Alimentação via painel solar

---

## 📑 Licença
Projeto desenvolvido para fins acadêmicos por **Suelen V. Fraga** – Universidade do Vale do Rio dos Sinos (UNISINOS). Uso livre para aprendizado e modificações não comerciais.


