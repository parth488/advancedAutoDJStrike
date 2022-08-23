#define pirPin 2
const int led_pin1 = 3;
int buzzer = 8;
const int led_pin2 = 4;
int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 500;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;
void buzz(){
  tone(buzzer, 1000);
}

void buzzoff(){
  tone(buzzer, 0);
  }

void setup() {
   Serial.begin(9600);
   pinMode(pirPin, INPUT);
}

void loop() {
   PIRSensor();
}

void PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         Serial.println("Motion detected.");
         buzz();
         digitalWrite( led_pin1,HIGH);
         digitalWrite( led_pin2,LOW);
         delay(50);
      }
      takeLowTime = true;
   }
   if(digitalRead(pirPin) == LOW) {
      if(takeLowTime){
         lowIn = millis();Serial.println(lowIn);takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > pause) {
         PIRValue = 0;
         lockLow = true;
         Serial.println("Motion ended.");
         digitalWrite(buzzer, LOW);
         digitalWrite( led_pin1,LOW);
         digitalWrite( led_pin2,HIGH);
         delay(50);
      }
   }
}




 
