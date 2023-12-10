#include "LiquidCrystal.h"
#include <DHT.h>

#define DHTPIN 3  // broche du capteur dht
#define DHTTYPE DHT11 // type de capteur dht

DHT dht(DHTPIN, DHTTYPE); // declaration du dht

// LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // declaration du lcd

const int CO2Pin = A0;  // pin analogique de lecture du capteur de CO2
const int greenLED = 8;
const int redLED = 9;

// variables 
const int TEMPERATURE_LOWER_LIMIT = 20;
const int TEMPERATURE_UPPER_LIMIT = 25;
const int HUMIDITY_LOWER_LIMIT = 30;
const int HUMIDITY_UPPER_LIMIT = 60;
const int CO2_UPPER_LIMIT = 800;
const int CO2_LIMIT = 1000;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("CO2: ");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(10, 0);
  lcd.print("ppm");
  lcd.setCursor(11, 1);
  lcd.print("C");
  lcd.setCursor(15, 1);
  lcd.print("%");
}

// fonction de convertion du CO2 lu
int convertToCO2(int rawValue) {
  const int rawMin = 160;
  const int rawMax = 400;
  const int co2Min = 400;
  const int co2Max = 1100;
  int co2Value = map(rawValue, rawMin, rawMax, co2Min, co2Max);
  return co2Value;
}

// fonction d'affichage sur le LCD
void afficherLCD(float temperature, int humidity, int ppm) {
  String formattedTemperature = String(temperature, 1);

  lcd.setCursor(9, 0);
  lcd.print(" ");

  lcd.setCursor(6, 0);
  lcd.print(convertToCO2(ppm));

  lcd.setCursor(6, 1);
  lcd.print(formattedTemperature);

  lcd.setCursor(13, 1);
  lcd.print(humidity);
}

// fonction d'affichage sur le Moniteur PC
void afficherMoniteur(float temperature, int humidity, int ppm) {
  String formattedTemperature = String(temperature, 1);
  String formattedHumidity = String(humidity);
  String formattedCO2 = String(convertToCO2(ppm));

  Serial.println("Taux de CO2 : " + formattedCO2 + " ppm\n");
  Serial.println("Temperature : " + formattedTemperature + " °C\n");
  Serial.println("Humidité : " + formattedHumidity + "%\n");
}

//fonction de l'etat de la led
void ledEtat(float temperature, int humidity, int ppm) {
  int tauxCO2 = convertToCO2(ppm);
  digitalWrite(greenLED, (temperature >= TEMPERATURE_LOWER_LIMIT && temperature <= TEMPERATURE_UPPER_LIMIT &&
                           humidity >= HUMIDITY_LOWER_LIMIT && humidity <= HUMIDITY_UPPER_LIMIT &&
                           tauxCO2 <= CO2_LIMIT) ? HIGH : LOW);
  digitalWrite(redLED, (tauxCO2 > CO2_UPPER_LIMIT) ? HIGH : LOW);
}

void loop() {
  int mq135Value = analogRead(CO2Pin);
  int co2Concentration = convertToCO2(mq135Value);

  int humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  afficherLCD(temperature, humidity, mq135Value);
  afficherMoniteur(temperature, humidity, mq135Value);
  ledEtat(temperature, humidity, mq135Value);
  delay(200);
}