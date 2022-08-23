 #include <ESP8266WiFi.h>  
 #include <ESP8266WebServer.h>  
 #include<WiFiManager.h> 
  void setup() {  
  Serial.begin(115200);  
  WiFiManager wifiManager;  
  wifiManager.autoConnect("AutoConnectAP","12345");  
  Serial.println("Connected.....");  
 }  
  void loop() {  
  // put your main code here, to run repeatedly:  
 }  
