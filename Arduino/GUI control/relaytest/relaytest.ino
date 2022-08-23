int val;
const int motor = 5;  
void setup()  
{  
Serial.begin(9600);
  pinMode(motor, OUTPUT);
}  
void loop()  
{  

val = 1;  // It will read the incoming or arriving data byte
Serial.println(val);  
if(val==1){
    digitalWrite(motor, HIGH);
  Serial.println("Current Flowing");
}
else{
  digitalWrite(motor, LOW);
  Serial.println("Current not Flowing");
}


delay(100);  
}  
