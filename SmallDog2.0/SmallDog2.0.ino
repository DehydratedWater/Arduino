#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150
#define SERVOMAX  600
byte pos[16] = {90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90};

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";
const byte txAddr[6] = "00001";
char mess[16] = {0};
int indexOfMess = 0;
bool isMessageReading = false;
bool isMessageFull = false;
bool isReading = false;
bool isFreshReading = false;
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
}


int getPos(int angle)
{
  return ((float)angle/180)*(SERVOMAX-SERVOMIN)+SERVOMIN;
}

void setAllServos()
{
  for(int i = 0; i < 16; i++)
  {
    pwm.setPWM(i, 0, getPos(pos[i]));
  }
}

void reset()
{
  for(int i = 0; i < 16; i++)
  {
    pos[i] = 90;
    pwm.setPWM(i, 0, getPos(90));
  }
}


byte angleBorder(char c)
{
    byte w = (byte)c;
    if(w<0)
      w = 0;
    if(w>180)
      w = 180;
    return w;
}
void useRadioData(char text[])
{
    for(int i = 0; i < 16; i++)
    {
      pos[i] = angleBorder(text[i]);
      pwm.setPWM(i, 0, getPos(pos[i]));
    }
    
}
void useRadioData(byte text[])
{
    for(int i = 0; i < 16; i++)
    {
      pos[i] = angleBorder(text[i]-1);
      pwm.setPWM(i, 0, getPos(pos[i]));
    }
    
}
void setServoPosRadio()
{
 // Serial.println(radio.available());
  radio.startListening();
  if (radio.available())
  {
    //delay(1);
    
    byte c[32] = {0};
    radio.read(&c, sizeof(c));
//    Serial.print("Odebrano wiadomosc ");
//    for(int i = 0 ; i < 32; i++)
//    {
//      Serial.print(c[i]);
//      Serial.print(" ");
//    }
//    Serial.println();
    for(int i = 0; i < 32; i++)
    {
      if(c[i]!=0)
      {
        if(!isReading)
        {
          if(c[i] == 182)
          {
            //Serial.println("Rozpoczeto czytanie");
            isReading = true;
            isFreshReading = true;
          }
          continue;
        }
        if(isReading)
        {
        if(c[i] == 182)
        {
          isReading = false;
          if(isFreshReading)
            isReading = true;
          if(indexOfMess == 16)
          {
         // Serial.println(mess);
         Serial.print("Odebrano wiadomosc ");
          for(int i = 0 ; i < 16; i++)
            {
               Serial.print((byte)mess[i]);
               Serial.print(" ");
            }
             Serial.println();
          }
          useRadioData(mess);
           indexOfMess=0;
           continue;
        }
        isFreshReading = false;  
        mess[indexOfMess] = c[i];
        indexOfMess++;
       
        }
      }
    }
  }
}

void sendMessage()
{
   radio.stopListening();
   char tab[32] = {0};
   String test = "WOLOlololo";
   test.toCharArray(tab, 32);
   radio.write(&tab, sizeof(tab));
   radio.startListening();
  
}

void setServoPosSerial()
{
  //Serial.println("Dostepne bajty ");
  //Serial.println(Serial.available());
  if(Serial.available()>=16)
  {
    Serial.println("Odczytywanie");
    char text[16] = {0};
    for(int i = 0; i < 16; i++)
    {
      text[i] = Serial.read();
    }
    Serial.println(text);
   useRadioData(text);
  }
}

void loop() {
setServoPosRadio();
setServoPosSerial();
//sendMessage();
}
