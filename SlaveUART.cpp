#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial mySerial(6,7);

LiquidCrystal_I2C lcd(0x27,16,2);

String data="";

void setup()
{
  mySerial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop()
{
  if(mySerial.available())
  {
    data=mySerial.readStringUntil('\n');

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print(data.substring(0,16));

    lcd.setCursor(0,1);

    if(data.length()>16)
      lcd.print(data.substring(16));
  }
}