#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>
RF24 radio(7, 8);

int wiad = 0;
const byte rxAddr[6] = "00001";

void setup()
{
  Serial.begin(250000);
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
  Serial.println("Rozpoczynanie nadawania");
}

void loop()
{
  if(Serial.available())
  {
  char tab[32] = {0};
  int index = 0;
  while(Serial.available()&&index<32)
  {
    tab[index] = Serial.read();
    index++;
  }
 
  Serial.println(tab);
    radio.write(&tab, sizeof(tab));
  }
  
//    String a = "LOSOWA WIADOMOSC xDDD "; 
//    a = a +wiad;
//    char tab[32] = {0};
//    for(int i = 0; i < a.length(); i++)
//    {
//      tab[i] = a[i];
//    }
//
//    radio.write(&tab, sizeof(tab));
//     Serial.println(tab);
//      
//    wiad++;
  //radio.write(&in, sizeof(in));
  // const char text[] = "Hello World";
 // radio.write(&text, sizeof(text));
  
//  delay(1000);
 // delay(1000);
}
