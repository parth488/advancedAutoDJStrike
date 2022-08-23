const int ldr_pin = 7;
const int led_pin1 = 5;
const int led_pin2 = 6;
void setup() {
  // put your setup code here, to run once:
    pinMode(ldr_pin,INPUT);
    pinMode(led_pin1,OUTPUT);
    pinMode(led_pin2,OUTPUT);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   if( digitalRead( ldr_pin ) == 1){
      digitalWrite( led_pin1,HIGH);
      digitalWrite( led_pin2,LOW);
      Serial.println("AUXILIARY LIGHTS On");
   }
   else{
      digitalWrite( led_pin1,LOW);
      digitalWrite( led_pin2,HIGH);
      Serial.println("AUXILIARY LIGHTS Off");
   }
   
   
   delay(200);
}
