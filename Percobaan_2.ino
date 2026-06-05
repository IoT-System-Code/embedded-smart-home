#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define PIR_PIN 2
#define BUZZER_PIN 8
#define TRIG_PIN 9
#define ECHO_PIN 10

long duration;
int distance;
int motion;

void setup() {

  Serial.begin(9600);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print(" SMART HOME ");
  lcd.setCursor(0,1);
  lcd.print("   READY    ");

  delay(2000);
  lcd.clear();
}

void loop() {

  // Baca PIR
  motion = digitalRead(PIR_PIN);

  // Baca Ultrasonic
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if(duration == 0)
    distance = 999;
  else
    distance = duration * 0.034 / 2;

  // ===== LCD BARIS 1 =====
  lcd.setCursor(0,0);

  if(motion == HIGH && distance <= 50)
  {
    lcd.print("PIR:1 ALARM!  ");
    tone(BUZZER_PIN,1000);
  }
  else if(motion == HIGH)
  {
    lcd.print("PIR:1 GERAK   ");
    noTone(BUZZER_PIN);
  }
  else
  {
    lcd.print("PIR:0 AMAN    ");
    noTone(BUZZER_PIN);
  }

  // ===== LCD BARIS 2 =====
  lcd.setCursor(0,1);
  lcd.print("JARAK:");
  lcd.print(distance);
  lcd.print("cm   ");

  // ===== SERIAL =====
  Serial.print("PIR=");
  Serial.print(motion);
  Serial.print(" | Jarak=");
  Serial.print(distance);
  Serial.println(" cm");

  delay(200);
}