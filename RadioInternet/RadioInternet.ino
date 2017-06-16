#include <string.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
void setup() {
  Serial.begin(250000);
  Serial.setTimeout(1);
  while(!Serial);

  radio.begin();
  radio.setRetries(15,15);
  Serial.println("Rozpoczeto Inicjalizacje modulu 1");
}

int commandChoose(String c)
{
  if(c[0]=='/')
  {
    Serial.println("Wykryto komende");
    if(c[1]=='S'&&c[2]=='P')
    {
      Serial.println("Komenda Set Parameters");
      return 0;
    }
    else if(c[1]=='S'&&c[2]=='W')
    {
       Serial.println("Komenda Start Writing");
       return 1;
    }
     else if(c[1]=='W'&&c[2]=='T')
    {
       Serial.println("Komenda Write Text");
       return 2;
    }
     else if(c[1]=='S'&&c[2]=='R')
    {
       Serial.println("Komenda Start Reading");
       return 3;
    }
     else if(c[1]=='G'&&c[2]=='T')
    {
       Serial.println("Komenda Get Text");
       return 4;
    }
     else if(c[1]=='S'&&c[2]=='L')
    {
       Serial.println("Komenda Start Listening");
       return 5;
    }
     else if(c[1]=='E'&&c[2]=='L')
    {
       Serial.println("Komenda End Listening");
       return 6;
    }
     else if(c[1]=='G'&&c[2]=='S')
    {
       Serial.println("Komenda Get State");
       return 7;
    }
    else
     {
       Serial.println("Brak Komendy");
       return -1;
    }
  }
  return -1;
};

void loop() {
  String com;
  
  com = Serial.readString();
  
  if(com!="")
  {
  int c = commandChoose(com);
  Serial.print("Wykryto komende: ");
  Serial.println(c);
  }
}







