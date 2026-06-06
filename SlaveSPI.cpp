#include <SPI.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

volatile boolean dataReady = false;
volatile String receivedData = "";

ISR (SPI_STC_vect)
{
  char c = SPDR;

  if(c == '\n')
  {
    dataReady = true;
  }
  else
  {
    receivedData += c;
  }
}

void setup()
{
  pinMode(MISO, OUTPUT);

  SPCR |= _BV(SPE);
  SPI.attachInterrupt();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("SMART HOME");
}

void loop()
{
  if(dataReady)
  {
    lcd.clear();

    lcd.setCursor(0,0);

    if(receivedData.length() > 16)
    {
      lcd.print(receivedData.substring(0,16));

      lcd.setCursor(0,1);
      lcd.print(receivedData.substring(16));
    }
    else
    {
      lcd.print(receivedData);
    }

    Serial.println(receivedData);

    receivedData = "";
    dataReady = false;
  }
}