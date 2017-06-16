#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150
#define SERVOMAX  600
//#define SERVOMIN  0
//#define SERVOMAX  1024
int pos[16] = {90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90};
int servoMatch[12] = {0,1,2,3,4,5,10,11,12,13,14,15};
const int legTab[4][3]={{2,4,0},{5,3,1},{10,11,14},{13,12,15}};

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";
const byte txAddr[6] = "00001";


bool isMessageReading = false;
bool isMessageFull = false;
char fullMessage[64] = {0};
int actualIndex = 0;
void setup() {
  Serial.begin(250000);
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  radio.openReadingPipe(0, txAddr);
  Serial.println("Rozpoczynanie nadawania SmallDog");
  
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();
  setAllServos();
//Serial.println("Znak zycia");
}


int getPos(int angle)
{
  return ((float)angle/180)*(SERVOMAX-SERVOMIN)+SERVOMIN;
}

void setAllServos()
{
  pwm.setPWM(0, 0, getPos(pos[0]));
  pwm.setPWM(1, 0, getPos(pos[1]));
  pwm.setPWM(2, 0, getPos(pos[2]));
  
  pwm.setPWM(3, 0, getPos(pos[3]));
  pwm.setPWM(4, 0, getPos(pos[4]));
  pwm.setPWM(5, 0, getPos(pos[5]));

  pwm.setPWM(10, 0, getPos(pos[10]));
  pwm.setPWM(11, 0, getPos(pos[11]));
  pwm.setPWM(12, 0, getPos(pos[12]));
  
  pwm.setPWM(13, 0, getPos(pos[13]));
  pwm.setPWM(14, 0, getPos(pos[14]));
  pwm.setPWM(15, 0, getPos(pos[15]));
}

void reset()
{
  for(int i = 0; i < 16; i++)
  {
    pos[i] = 90;
    pwm.setPWM(i, 0, getPos(90));
  }
}

int getNumberFromChar(char a, char b, char c)
{
  return (a-'0')*100+(b-'0')*10+(c-'0');
}



void sendRetryMessage()
{
//  if(Serial.available())
//  {
//   radio.stopListening();
//   char tab[32] = {0};
//   int index = 0;
//  while(Serial.available()&&index<32)
//  {
//    tab[index] = Serial.read();
//    index++;
//  }
//
//    Serial.println(tab);
//    radio.write(&tab, sizeof(tab));
//    radio.startListening();
//  }
//Serial.println("Nadawanie");
//radio.stopListening();
//    char tab[9] = {'P','o','l','a','c','z','o','n','o'};
//    radio.write(&tab, sizeof(tab));
//    radio.startListening();
}

void useRadioData(char text[])
{
   if(text[0] == 'S')
     {
        int servoNum = getNumberFromChar('0', text[2], text[3]);
        int servoAngle = getNumberFromChar(text[5], text[6], text[7]);
        if(servoNum<0)
          servoNum = 0;
    if(servoNum>15)
      servoNum = 15;
    if(servoAngle>180)
      servoAngle = 180;
    if(servoAngle<0)
      servoAngle = 0;
        pos[servoNum] = servoAngle;
        pwm.setPWM(servoNum, 0, getPos(servoAngle));
     }
     else if(text[0] == 'R')
     {
      reset();
      setAllServos();
     }
     else if(text[0] == 'A')
     {
      
      int servoAngle;
      for(int i = 0; i < 16; i++)
      {
        Serial.print("Odebrano wiadomosc ");
        Serial.println(text);
          servoAngle = getNumberFromChar(text[i*3+1], text[i*3+2], text[i*3+3]);
          if(servoAngle>180)
            servoAngle = 180;
          if(servoAngle<0)
            servoAngle = 0;
            Serial.print(i);
            Serial.print(" ");
            Serial.println(servoAngle);
          //pwm.setPWM(i, 0, getPos(servoAngle));
      }
     }
     else if(text[0] == 'L')
     {
     int legIndex = getNumberFromChar('0', '0', text[1]);
     int servoAngle1 = getNumberFromChar(text[2], text[3], text[4]);
     int servoAngle2 = getNumberFromChar(text[5], text[6], text[7]);
     int servoAngle3 = getNumberFromChar(text[8], text[9], text[10]);

     pos[legTab[legIndex][0]] = servoAngle1;
     pwm.setPWM(legTab[legIndex][0], 0, getPos(servoAngle1));
     pos[legTab[legIndex][1]] = servoAngle2;
     pwm.setPWM(legTab[legIndex][1], 0, getPos(servoAngle2));
     pos[legTab[legIndex][2]] = servoAngle3;
     pwm.setPWM(legTab[legIndex][2], 0, getPos(servoAngle3));
     }
     else
     {
      //Serial.println(text);
     }
    
    
}

void setServoPosRadio()
{
  radio.startListening();
  if (radio.available())
  {
    
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    useRadioData(text);
    Serial.println(text);
    

   // Serial.println(text);
  }
}

void setServoPosSerial()
{
  if(Serial.available())
  {
    int index = Serial.parseInt();
    int angle = Serial.parseInt();
    if(index<0)
      index = 0;
    if(index>15)
      index = 15;
    if(angle>180)
      angle = 180;
    if(angle<0)
      angle = 0;
//    if(index>-1&&index<12&&angle>-1&&angle<180)
//    {
      pos[index] = angle;
      pwm.setPWM(index, 0, getPos(angle));
      Serial.print("Ustawiono serwo nr: ");
      Serial.print(index);
      Serial.print(" na kat: ");
      Serial.println(angle);
//    }
    
  }
}

void loop() {
 //Serial.println("Znak zycia");
setServoPosRadio();
setServoPosSerial();
sendRetryMessage();
}
