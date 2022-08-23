

#include "DHT.h"

#define DHTPIN 5  

#define DHTTYPE DHT11   // DHT 11
const int ldrpin= 4;
const int ledpin=13;

DHT dht(DHTPIN, DHTTYPE);
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#include <FirebaseESP8266.h>

//1. Change the following info
#define WIFI_SSID "TP-LINK_9382"
#define WIFI_PASSWORD "15299185"
#define FIREBASE_HOST "https://nodemcu-b32d9-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "TDKBQQHVbsiKMZWrHoCTjDDVNzurnKuSIkBTsxJg"

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData fbdo;

String path = "/Sensors";
void setup() {
  pinMode(ldrpin, INPUT);
  pinMode(ledpin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
//3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);
  Serial.println(F("DHT11 interface"));
  dht.begin();
}

void loop() {
  
  delay(1500);
 int ldrstatus=digitalRead(ldrpin);
 Serial.println(ldrstatus);
  

 
  float h = dht.readHumidity();
 
  float t = dht.readTemperature();
 
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  //firebase pushing data

  if (Firebase.setInt(fbdo, path + "/DHT11/Humidity", h) && Firebase.setInt(fbdo, path + "/DHT11/Temperature", t) &&  Firebase.setInt(fbdo, path + "/LDRLightLevel", ldrstatus))
    {
      Serial.println("PASSED");
      if(ldrstatus==1){
        digitalWrite(ledpin, HIGH);}
      else{
        digitalWrite(ledpin, LOW);
        }
    }
    else
    {
      Serial.println("FAILED");
          }
}
