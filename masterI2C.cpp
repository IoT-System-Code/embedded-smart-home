#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

#define PIR_PIN 2
#define BUZZER_PIN 8
#define TRIG_PIN 9
#define ECHO_PIN 10

#define SS_PIN 4
#define RST_PIN 3

MFRC522 rfid(SS_PIN, RST_PIN);

long duration;
int distance;
int motion;

String dataKirim;

void setup()
{
  Serial.begin(9600);

  Wire.begin();

  SPI.begin();
  rfid.PCD_Init();

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop()
{
  motion = digitalRead(PIR_PIN);

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2;

  String rfidStatus = "NOCARD";

  if (rfid.PICC_IsNewCardPresent() &&
      rfid.PICC_ReadCardSerial())
  {
    rfidStatus = "CARD";

    for (byte i=0;i<rfid.uid.size;i++)
    {
      Serial.print(rfid.uid.uidByte[i],HEX);
      Serial.print(" ");
    }
    Serial.println();

    rfid.PICC_HaltA();
  }

  if(motion==HIGH && distance<50)
      tone(BUZZER_PIN,1000);
  else
      noTone(BUZZER_PIN);

  dataKirim =
      String(motion) + "," +
      String(distance) + "," +
      rfidStatus;

  Wire.beginTransmission(8);

  for(int i=0;i<dataKirim.length();i++)
  {
    Wire.write(dataKirim[i]);
  }

  Wire.endTransmission();

  delay(500);
}