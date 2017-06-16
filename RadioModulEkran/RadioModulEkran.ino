#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

RF24 radio(7, 8);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int wiad = 0;
const byte rxAddr[6] = "00001";
const byte txAddr[6] = "00001";
void setup()
{

  radio.begin();
  radio.setRetries(15, 15);
  radio.openReadingPipe(0, txAddr);
   lcd.begin(20,4);   // Inicjalizacja LCD 2x16
  
  lcd.backlight(); // zalaczenie podwietlenia 
  lcd.setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
  lcd.print("Hello, world!");
  delay(500);

  Serial.println("Rozpoczynanie nadawania");
}

void loop()
{
 

  radio.startListening();
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    lcd.clear();
    lcd.setCursor(0,0);
    for(int i = 0; i < 20; i++)
    {
      if(text[i]==0)
      {
      break;
      }
      lcd.print(text[i]);
    }
    lcd.setCursor(0,1);
     for(int i = 20; i < 32; i++)
    {
      if(text[i]==0)
      {
      break;
      }
      lcd.print(text[i]);
    }
  }
  



}
