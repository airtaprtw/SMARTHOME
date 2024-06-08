#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int motionPin = 11; // Pin digital untuk sensor gerakan
const int LDRPin = A0; // Pin analog untuk sensor LDR
const int LEDPin = 4; // Pin digital untuk LED
const int soundPin = A1; // Pin analog untuk sensor suara
const int buzzerPin = 2; // buzzer
const int TRIGPin = 7;          
const int ECHOPin = 8;
const int LCD = A4;
long timer;
int jarak;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(motionPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  pinMode(ECHOPin, INPUT);
  pinMode(TRIGPin, OUTPUT);
  Serial.begin(9600);

  int positionCounter;
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Embedded");
  lcd.setCursor(0, 1);
  lcd.print("UAP");

  for (positionCounter = 0; positionCounter < 26; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay (300);
  }
    lcd.clear();
}

void loop() {
  int motionValue = digitalRead(motionPin);
  int lightValue = analogRead(LDRPin);
  int soundValue = analogRead(soundPin);
  

  lcd.setCursor(0, 0);
  lcd.print("Motion: ");
  lcd.print(motionValue);

  lcd.setCursor(0, 1);
  lcd.print("Sound: ");
  lcd.print(soundValue);

  Serial.print("Motion: ");
  Serial.print(motionValue);
  Serial.print("\tLight: ");
  Serial.print(lightValue);
  Serial.print("\tSound: ");
  Serial.println(soundValue);
  
  digitalWrite(TRIGPin, LOW);                   
  delayMicroseconds(2);
  digitalWrite(TRIGPin, HIGH);                  
  delayMicroseconds(10);
  digitalWrite(TRIGPin, LOW);                   

  timer = pulseIn(ECHOPin, HIGH);
  jarak = timer/58;
  delay(1000);

  Serial.print("Jarak = ");
  Serial.print(jarak);
  Serial.print(" cm");
  Serial.println();


  // Jika cahaya rendah, aktifkan LED
  if (lightValue > 500) {
    digitalWrite(LEDPin, HIGH);
    delay(2000);
  } else {
    digitalWrite(LEDPin, LOW);
    delay(1000);

  }
  

  if (jarak < 100) {;
    tone(buzzerPin, 1000);
  } else {
    noTone(buzzerPin);
  }
  
  delay(1000); // Delay untuk stabilitas
}

