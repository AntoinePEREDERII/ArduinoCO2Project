#include <DHT.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

#define DHTPIN 0 // pin GPIO 0 correspond à D3
#define DHTTYPE DHT11

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// sensor informations
DHT dht(DHTPIN, DHTTYPE);
const int CO2Pin = A0;

int co2Concentration, humidity;
float temperature;


void setup() {
  Serial.begin(115200);
  dht.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

int convertToCO2(int rawValue) {
  const int rawMin = 160;
  const int rawMax = 400;
  const int co2Min = 400;
  const int co2Max = 1100;
  int co2Value = map(rawValue, rawMin, rawMax, co2Min, co2Max);
  return co2Value;
}

void loop() {
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  co2Concentration = convertToCO2(analogRead(CO2Pin));
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // set the fields with the values
  ThingSpeak.setField(1, co2Concentration);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, temperature);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(20000); // Wait 20 seconds to update the channel again
}