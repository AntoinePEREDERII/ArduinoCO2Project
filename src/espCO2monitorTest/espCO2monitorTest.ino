#include <DHT.h>
#include <ESP8266WiFi.h>

#define DHTPIN 0 // pin GPIO 0 corrspond à d3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int CO2Pin = A0;
int co2Concentration, humidity;
float temperature;

void setup() {
  Serial.begin(115200);
  dht.begin();
}

int convertToCO2(int rawValue) {
  const int rawMin = 160;
  const int rawMax = 400;
  const int co2Min = 400;
  const int co2Max = 1100;
  int co2Value = map(rawValue, rawMin, rawMax, co2Min, co2Max);
  return co2Value;
}

void afficherMoniteur(float temperature, int humidity, int ppm) {
  String formattedTemperature = String(temperature, 1);
  String formattedHumidity = String(humidity);
  String formattedCO2 = String(ppm);

  Serial.println("Taux de CO2 : " + formattedCO2 + " ppm\n");
  Serial.println("Temperature : " + formattedTemperature + " °C\n");
  Serial.println("Humidité : " + formattedHumidity + "%\n");
}

void loop() {
  co2Concentration = convertToCO2(analogRead(CO2Pin));
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  afficherMoniteur(temperature, humidity, co2Concentration);
  delay(200);
}
