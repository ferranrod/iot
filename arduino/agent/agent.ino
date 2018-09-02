/*
 * Configuración IDE:  https://www.arduino.cc/en/Guide/ArduinoMega2560
 * Language reference: https://www.arduino.cc/reference/en/
 */
#include <config.h>
#include <Wire.h>
#include <dht.h>    // sensor temperatura DHT11
/*
 * The LiquidCrystal() function sets the pins the Arduino uses to connect to the LCD.
 * You can use any of the Arduino’s digital pins to control the LCD.
 * Just put the Arduino pin numbers inside the parentheses in this order: LiquidCrystal(RS, E, D4, D5, D6, D7). RS, E, D4, D5, D6, D7 are the LCD pins.
 */
#include <LiquidCrystal.h>
#include <Wire.h>

#define DELAY 5000          // tiempo de espera en ms
dht DHT;
#define DHT11_PIN 4         // pin sensor de temperatura y humedad
byte sensorPresencePin = 3; // pin sensor de presencia
byte indicatorPresence = 13;
// LiquidCrystal(rs, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // pins display lcd

/*
 * Inicialización
 */
void setup() {
  pinMode(sensorPresencePin, INPUT);
  pinMode(indicatorPresence, OUTPUT);
  Serial.begin(9600);

  //lcd.clear();
  //lcd.noDisplay();
  initializeDisplay();
}

/*
 * Función principal
 */
void loop() {
  /* Sensor temperatura y humedad */
  int chk = DHT.read11(DHT11_PIN);
  Serial.println();
  Serial.print("{\"T\":");
  Serial.print(DHT.temperature);

  Serial.print(", \"H\":");
  Serial.print(DHT.humidity);

  /* Sensor luz */
  int sensorLight = analogRead(A0); // leer el valor del sensor en el analógico 0
  Serial.print(", \"L\":");
  Serial.print(sensorLight);

  /* Sensor gas */
  int sensorGas = analogRead(A1);   // leer el valor del gas en el analógico 1
  Serial.print(", \"G\":");
  Serial.print(sensorGas);
 
  /* Sensor de presencia */
  byte sensorPresence = digitalRead(sensorPresencePin);
  digitalWrite(indicatorPresence, sensorPresence);
  Serial.print(", \"P\":");
  Serial.print(sensorPresence);
  Serial.print("}");

  displayData(DHT.temperature, DHT.humidity, sensorLight, sensorGas, sensorPresence);

  delay(DELAY); // Espera n segundos
}



void initializeDisplay() {
  lcd.begin(16, 2);   // sets the dimensions of the LCD (columns, rows)

  lcd.setCursor(0,0);
  lcd.write("T=");

  lcd.setCursor(8,0);
  lcd.write("H=");

  lcd.setCursor(0,1); // places the cursor (and any printed text) at any position on the screen (column, row)(0-15 and 0-1 respectively)
  lcd.write("L=");

  lcd.setCursor(7,1); // places the cursor (and any printed text) at any position on the screen (column, row)(0-15 and 0-1 respectively)
  lcd.write("G=");

  lcd.setCursor(13, 1);
  lcd.write("P=");
}

/*
 * lcd.print():
 * print text to the LCD. It can be used in the void setup() section or the void loop() section of the program
 * can print numbers in decimal, binary, hexadecimal, and octal bases
 */
void displayData(double Temp, double Hum, int Light, int Gas, byte Presence) {
  lcd.setCursor(2,0);
  lcd.print(Temp);

  lcd.setCursor(10,0);
  lcd.print(Hum);

  lcd.setCursor(2,1);
  lcd.print(Light);

  lcd.setCursor(9,1);
  lcd.print(Gas);

  lcd.setCursor(15,1);
  lcd.print(Presence);
}

