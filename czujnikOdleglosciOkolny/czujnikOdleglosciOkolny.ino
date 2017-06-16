#include <Servo.h> 
 
Servo myservo;  
int Trig1 = 2; 
int Echo1 = 3;  
int CM1;       
long CZAS1;               
int Trig2 = 4; 
int Echo2 = 5;  
int CM2;       
long CZAS2;  
int pos = 0;   
int del = 1000;
void setup() 
{ 
  Serial.begin(9600); 
  pinMode(Trig1, OUTPUT); 
  pinMode(Echo1, INPUT);
  pinMode(Trig2, OUTPUT); 
  pinMode(Echo2, INPUT); 
 // Serial.println("Test czujnika odleglosci");
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 

  for(pos = 0; pos < 180; pos += 1)
  {        
    myservo.write(pos);          
     pomiar_odleglosci();
    drawRes(); 
  } 
  for(pos = 178; pos>0; pos-=1) 
  {                                
    myservo.write(pos); 
     pomiar_odleglosci();
    drawRes(); 
  } 
 
 

} 

void drawRes()
{
  Serial.print(pos);
  Serial.print(" ");
  Serial.print(CM1);
  Serial.print(" "); 
  Serial.println(CM2);  
}
void pomiar_odleglosci ()
{
      delay(del);
  digitalWrite(Trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig1, LOW);
  CZAS1 = pulseIn(Echo1, HIGH);
  CM1 = CZAS1 / 58;   

  digitalWrite(Trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig2, LOW);
  CZAS2 = pulseIn(Echo2, HIGH);
  CM2 = CZAS2 / 58;              
}


