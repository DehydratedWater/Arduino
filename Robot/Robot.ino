#include <Servo.h> 
Servo s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12;
int pos[12];

void setup() 
{
  s1.attach(0);
  s2.attach(1);
  s3.attach(2);
  s4.attach(3);
  s5.attach(4);
  s6.attach(5);
  s7.attach(6);
  s8.attach(7);
  s9.attach(8);
  s10.attach(9);
  s11.attach(10);
  s12.attach(11);
  
  pos[0] = 90;
  pos[1] = 90;
  pos[2] = 90;
  pos[3] = 90;
  pos[4] = 90;
  pos[5] = 90;
  pos[6] = 90;
  pos[7] = 90;
  pos[8] = 90;
  pos[9] = 90;
  pos[10] = 90;
  pos[11] = 90;

  s1.write(pos[0]);
  s2.write(pos[1]);
  s3.write(pos[2]);
  s4.write(pos[3]);
  s5.write(pos[4]);
  s6.write(pos[5]);
  s7.write(pos[6]);
  s8.write(pos[7]);
  s9.write(pos[8]);
  s10.write(pos[9]);
  s11.write(pos[10]);
  s12.write(pos[11]);
  Serial.begin(250000);
  while(!Serial){}
Serial.println("Start");
}

void loop() 
{
  if(Serial.available())
  {
  Serial.println("Odebrano dane");
  
  pos[0] = Serial.parseInt();
  pos[1] = Serial.parseInt();
  pos[2] = Serial.parseInt();
  pos[3] = Serial.parseInt();
  pos[4] = Serial.parseInt();
  pos[5] = Serial.parseInt();
  pos[6] = Serial.parseInt();
  pos[7] = Serial.parseInt();
  pos[8] = Serial.parseInt();
  pos[9] = Serial.parseInt();
  pos[10] = Serial.parseInt();
  pos[11] = Serial.parseInt();
  
  Serial.print(pos[0]);
  Serial.print(" ");
  Serial.print(pos[1]);
  Serial.print(" ");
  Serial.print(pos[2]);
  Serial.print(" ");
  Serial.print(pos[3]);
  Serial.print(" ");
  Serial.print(pos[4]);
  Serial.print(" ");
  Serial.print(pos[5]);
  Serial.print(" ");
  Serial.print(pos[6]);
  Serial.print(" ");
  Serial.print(pos[7]);
  Serial.print(" ");
  Serial.print(pos[8]);
  Serial.print(" ");
  Serial.print(pos[9]);
  Serial.print(" ");
  Serial.print(pos[10]);
  Serial.print(" ");
  Serial.println(pos[11]);
  s1.write(pos[0]);
  s2.write(pos[1]);
  s3.write(pos[2]);
  s4.write(pos[3]);
  s5.write(pos[4]);
  s6.write(pos[5]);
  s7.write(pos[6]);
  s8.write(pos[7]);
  s9.write(pos[8]);
  s10.write(pos[9]);
  s11.write(pos[10]);
  s12.write(pos[11]);
  delay(20);
  }
  

}
