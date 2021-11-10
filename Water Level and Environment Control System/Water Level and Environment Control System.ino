#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(46, 47, 48, 49, 50, 51);
LiquidCrystal lcd2(39, 40, 41, 42, 43, 44);

int IRSensor = 53;
Servo myservo;

int servoPos = 0 ;

int lmval = 0;
int lm35 = A0;
int lmval2 = 0;
int lm352 = A1;

int ldp1 = 27;
int ldp2 = 26;
int ldp3 = 25;
int ldp4 = 24;
int ldp5 = 23;

const int buzzer = 30;
const int trigPin = 31;
const int echoPin = 32;
long duration;
int distance;
int motorF = 34;
int motorR = 35;

void setup() {
  // put your setup code here, to run once:
  pinMode(IRSensor, INPUT);
  myservo.attach(52);
  lcd.begin(16, 2);
  lcd2.begin(16, 2);
  pinMode(ldp1, OUTPUT);
  pinMode(ldp2, OUTPUT);
  pinMode(ldp3, OUTPUT);
  pinMode(ldp4, OUTPUT);
  pinMode(ldp5, OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(motorR,OUTPUT);
  pinMode(motorF,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorStatus = digitalRead(IRSensor);

  if (sensorStatus == 1) {
    for (servoPos = 0 ; servoPos <= 70; servoPos = servoPos + 1) {
      myservo.write(servoPos);
      delay(10);
    }
    delay(2000);
    for (servoPos = 70; servoPos >= 0; servoPos = servoPos - 1) {
      myservo.write(servoPos);
      delay(10);
    }
  }


  lmval = analogRead(lm35);
  float millivolts = (lmval / 1024.0) * 5 * 1000;
  float cel = millivolts / 10;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pool Temp: " + String(cel));
  lcd.setCursor(0, 1);
  lcd.print("degree Celcius");

  lmval2 = analogRead(lm352);
  float millivolts2 = (lmval2 / 1024.0) * 5 * 1000;
  float cel2 = millivolts2 / 10;
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("Air Temp: " + String(cel2));
  lcd2.setCursor(0, 1);
  lcd2.print("degree Celcius");
  delay(1000);
  
  digitalWrite(trigPin,LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034/2;
  
  if(distance>=0 && distance <= 20){
    light(ldp1,1);
    light(ldp2,1);
    light(ldp3,1);
    motorOff();
    light(ldp4,1);
    light(ldp5,1);
    noTone(buzzer); 
  }else if(distance>=21 && distance <= 40){
    light(ldp1,0);
    light(ldp2,1);
    light(ldp3,1);
    light(ldp4,1);
    light(ldp5,1);
    motorOff();
    noTone(buzzer); 
  }else if(distance>=41 && distance <= 60){
    light(ldp1,0);
    light(ldp2,0);
    light(ldp3,1);
    light(ldp4,1);
    light(ldp5,1);
    noTone(buzzer); 
    motorOff();
  }else if(distance>=61 && distance <= 80){
    light(ldp1,0);
    light(ldp2,0);
    light(ldp3,0);
    light(ldp4,1);
    light(ldp5,1);
    noTone(buzzer); 
    motorOff();
  }else if(distance>=81 && distance <= 100){
    light(ldp1,0);
    light(ldp2,0);
    light(ldp3,0);
    light(ldp4,0);
    light(ldp5,1);
    tone(buzzer,1000);
    motorOn();
  }

  
}


void motorOn(){
  digitalWrite(motorF,HIGH);
  digitalWrite(motorR,LOW);
}

void motorOff(){
  digitalWrite(motorF,LOW);
  digitalWrite(motorR,LOW);
}

void light(int led, int a){
  if(a==1){
    digitalWrite(led,HIGH);
  }else{
    digitalWrite(led,LOW);
  }
}
