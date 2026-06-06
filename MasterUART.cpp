#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(6,7);

#define PIR_PIN 2
#define BUZZER_PIN 8
#define TRIG_PIN 9
#define ECHO_PIN 10

#define SS_PIN 4
#define RST_PIN 3

MFRC522 rfid(SS_PIN,RST_PIN);

long duration;
int distance;
int motion;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  pinMode(PIR_PIN,INPUT);
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
}

void loop()
{
  motion=digitalRead(PIR_PIN);

  digitalWrite(TRIG_PIN,LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN,LOW);

  duration=pulseIn(ECHO_PIN,HIGH);

  distance=duration*0.034/2;

  String card="NOCARD";

  if(rfid.PICC_IsNewCardPresent() &&
     rfid.PICC_ReadCardSerial())
  {
      card="CARD";
      rfid.PICC_HaltA();
  }

  String data =
  String(motion)+","+
  String(distance)+","+
  card;

  mySerial.println(data);

  delay(500);
}