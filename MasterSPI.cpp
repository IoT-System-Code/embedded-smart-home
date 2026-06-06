#include <SPI.h>
#include <MFRC522.h>

#define PIR_PIN 2
#define RST_PIN 3
#define RFID_SS 4

#define SLAVE_SS 7

#define BUZZER_PIN 8
#define TRIG_PIN 9
#define ECHO_PIN 10

MFRC522 rfid(RFID_SS, RST_PIN);

long duration;
int distance;
int motion;

void sendString(String data)
{
  digitalWrite(SLAVE_SS, LOW);

  for(int i=0;i<data.length();i++)
  {
    SPI.transfer(data[i]);
  }

  SPI.transfer('\n');

  digitalWrite(SLAVE_SS, HIGH);
}

void setup()
{
  Serial.begin(9600);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(SLAVE_SS, OUTPUT);
  digitalWrite(SLAVE_SS, HIGH);

  SPI.begin();

  rfid.PCD_Init();
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

  String cardStatus = "NOCARD";

  if(rfid.PICC_IsNewCardPresent() &&
     rfid.PICC_ReadCardSerial())
  {
      cardStatus = "CARD";

      Serial.print("UID: ");

      for(byte i=0;i<rfid.uid.size;i++)
      {
          Serial.print(rfid.uid.uidByte[i],HEX);
          Serial.print(" ");
      }

      Serial.println();

      rfid.PICC_HaltA();
  }

  if(motion == HIGH && distance < 50)
      tone(BUZZER_PIN,1000);
  else
      noTone(BUZZER_PIN);

  String data =
      String(motion) + "," +
      String(distance) + "," +
      cardStatus;

  sendString(data);

  Serial.println(data);

  delay(500);
}