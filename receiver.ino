#include <SoftwareSerial.h>

SoftwareSerial btSerial(3, 4);
SoftwareSerial sim8001(10, 11);

const int led = 2;
const int buzzer = 5;
const int vibrationMotor = 6;
const int tiltSensor = 12;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(vibrationMotor, OUTPUT);
  pinMode(tiltSensor, INPUT);
  Serial.begin(9600);
  btSerial.begin(9600);
  sim8001.begin(9600);
}

void loop() {
  // Serial monitor
  if (Serial.available() > 0){
    char status = Serial.read();
    if(status == '1'){
      Serial.println("Car is overspeeding!");
      digitalWrite(led, HIGH);
      tone(buzzer, 1000);
      analogWrite(vibrationMotor, 255);
    } else if(status == '0'){
      Serial.println("Monitoring speed...");
      digitalWrite(led, LOW);
      noTone(buzzer);
      analogWrite(vibrationMotor, 0);
    }
  }

  // Bluetooth
  if (btSerial.available() > 0){
    char btStatus = btSerial.read();
    if(btStatus == '1'){
      btSerial.println("Car is overspeeding!");
      digitalWrite(led, HIGH);
      tone(buzzer, 1000);
      analogWrite(vibrationMotor, 255);
    } else if(btStatus == '0'){
      btSerial.println("Monitoring speed...");
      digitalWrite(led, LOW);
      noTone(buzzer);
      analogWrite(vibrationMotor, 0);
    }
  }
  
  // GSM Module
  if (sim8001.available() > 0){
    char gsmStatus = sim8001.read();
    if(gsmStatus == '1'){
      sim8001.println("Car is overspeeding!");
      digitalWrite(led, HIGH);
      tone(buzzer, 1000);
      analogWrite(vibrationMotor, 255);
    } else if(gsmStatus == '0'){
      sim8001.println("Monitoring speed...");
      digitalWrite(led, LOW);
      noTone(buzzer);
      analogWrite(vibrationMotor, 0);
    }
  }
  
  // Tilt Sensor reading
  int A = digitalRead(tiltSensor);
  Serial.print("Tilt=");
  Serial.println(A);
  if(A == LOW){
    Serial.println("Car tilt detected");
  }
}
