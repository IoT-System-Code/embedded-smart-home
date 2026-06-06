#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

String dataMasuk="";

void receiveEvent(int howMany)
{
  dataMasuk="";

  while(Wire.available())
  {
    char c = Wire.read();
    dataMasuk += c;
  }
}

void setup()
{
  Wire.begin(8);

  Wire.onReceive(receiveEvent);

  lcd.init();
  lcd.backlight();

  lcd.print("SMART HOME");
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print(dataMasuk);

  delay(200);
}