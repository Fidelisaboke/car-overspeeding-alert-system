#include <LiquidCrystal.h>

const int buzzer = 3;
const int led = 2;
const int speedSensor = A0;
const int speedLimit = 110;

LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

int previousSpeed = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(speedSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int analogInput = analogRead(speedSensor);
  int vehicleSpeed = map(analogInput, 0, 1023, 0, 255);
  
  if (vehicleSpeed != previousSpeed) {
  	lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print("Speed: ");
  	lcd.setCursor(0, 1);
  	lcd.print(vehicleSpeed);
    previousSpeed = vehicleSpeed;
  }
  
  if (vehicleSpeed > speedLimit) {
    digitalWrite(led, HIGH);
    tone(buzzer, 1000);
    Serial.write('1');
  }
  else {
    digitalWrite(led, LOW);
    noTone(buzzer);
    Serial.write('0');
  }
}

