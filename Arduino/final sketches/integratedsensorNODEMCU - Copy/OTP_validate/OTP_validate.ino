#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11
const int ldrpin= 14;
const int ledPin=0;
const int ledpin1=12;
#define pirPin 5
int pinSpeaker = 4;
int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 2000;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;
DHT dht(DHTPIN, DHTTYPE);
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>



#include <FirebaseESP8266.h>

//1. Change the following info
#define WIFI_SSID "TP-LINK_9382"
#define WIFI_PASSWORD "15299185"
#define FIREBASE_HOST "https://advanced-auto-7de27.firebaseio.com/"
#define FIREBASE_AUTH "sltLK5zL7rdhr6tnXuxNzotOTvzUAatpLOTByf2K"


//2. Define FirebaseESP8266 data object for data sending and receiving

FirebaseData fbdo;


int printResult(FirebaseData &data)
{ int number;
  
  if (data.dataType() == "int")
    number=data.intData();////////////////////////////////////
    return number;}



String path = "/Sensors";
String path_val = "/Validation";
void setup() {
   pinMode(ldrpin, INPUT);
   pinMode(ledpin1, OUTPUT);
   pinMode(pirPin, INPUT);
   pinMode(pinSpeaker, OUTPUT);
   pinMode(LED_BUILTIN, OUTPUT);
   //pinMode(buzzer, OUTPUT);
   pinMode(ledPin, OUTPUT); // declare LED as output 
   //pinMode(inputPin, INPUT); // declare Infrared sensor as input
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
void PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         Serial.println("Motion detected.");
         tone(4, 2000, 3000);
         
         
         delay(50);
      }
      takeLowTime = true;
   }
   if(digitalRead(pirPin) == LOW) {
      if(takeLowTime){
         lowIn = millis();takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > pause) {
         PIRValue = 0;
         lockLow = true;
         Serial.println("Motion ended.");
         noTone(4);
         delay(50);
      }
   }
}
void loop() {
  
  
  int sent_otp,received_otp;
   if (Firebase.getInt(fbdo, path_val + "/sent"))
   {   sent_otp=printResult(fbdo);
       //Serial.println(sent_otp);
   }
   
   if (Firebase.getInt(fbdo, path_val + "/received"))
   {   received_otp=printResult(fbdo);
       //Serial.println(received_otp);
   }
   if(sent_otp == received_otp){
    noTone(4);
    Serial.println("match");
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    
   }
   else if(sent_otp != received_otp){
    PIRSensor();
    Serial.println("no match");
    digitalWrite(ledPin, LOW);
   }

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
        digitalWrite(ledpin1, HIGH);}
      else{
        digitalWrite(ledpin1, LOW);
        }
    }
    else
    {
      Serial.println("FAILED");
          }

  
   
 
}
