
const int ledPin=0;
//int inputPin = 13; // choose input pin (for Infrared sensor) 
//int val = 0; // variable for reading the pin status 
//const int buzzer =  4;//digital2 of nodemcu
#define pirPin 5
int pinSpeaker = 4;
int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 2000;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
int printResult(FirebaseData &data)
{ int number;
  if (data.dataType() == "int")
    number=data.intData();////////////////////////////////////
    return number;}


#include <FirebaseESP8266.h>

//1. Change the following info
#define WIFI_SSID "TP-LINK_9382"
#define WIFI_PASSWORD "15299185"
#define FIREBASE_HOST "https://advanced-auto-7de27.firebaseio.com/"
#define FIREBASE_AUTH "sltLK5zL7rdhr6tnXuxNzotOTvzUAatpLOTByf2K"

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData fbdo;

String path = "/Validation";
void setup() {
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
  
  
}
void PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         Serial.println("Motion detected.");
         tone(4, 2000, 3000);
         digitalWrite(ledPin, HIGH);
         delay(100);
         digitalWrite(ledPin, LOW);
         delay(100);
         digitalWrite(ledPin, HIGH);
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
   if (Firebase.getInt(fbdo, path + "/sent"))
   {   sent_otp=printResult(fbdo);
   }
   
   if (Firebase.getInt(fbdo, path + "/received"))
   {   received_otp=printResult(fbdo);
   }
   if(sent_otp == received_otp){
    noTone(4);
    Serial.println("match");
   }
   else if(sent_otp != received_otp){
    PIRSensor();
    Serial.println("no match");
   }
   
  

delay(500);
}
