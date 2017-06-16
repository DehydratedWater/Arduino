#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>
RF24 radio(7, 8);

int wiad = 0;
const byte rxAddr[6] = "00001";
const byte txAddr[6] = "00001";
void setup()
{
  Serial.begin(250000);
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  radio.openReadingPipe(0, txAddr);
  Serial.println("Rozpoczynanie nadawania");
}

void loop()
{
  radio.startListening();
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    
    Serial.println(text);
  }
  
  if(Serial.available())
  {
   radio.stopListening();
   byte tab[32] = {0};
   int index = 0;
  while(Serial.available()&&index<32)
  {
    tab[index] = Serial.read();
    index++;
  }

    //Serial.println(tab);
    radio.write(&tab, sizeof(tab));
    radio.startListening();
  }


}
