#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>

LiquidCrystal lcd(47, 48, 50, 51, 52, 53);
const int buzzer = 45;
int ledpin1 = 13;
int ledpin2 = 12;


const byte ROWS = 4;
const byte COLS = 3;

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28};

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '='},
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int IRSensor = 46;
bool pass = false;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(IRSensor, INPUT);
  pass = false;
  pinMode(buzzer,OUTPUT);
}

//Serial.println("Hi" + String(a));
char ch[100];
int chcount = 0;

void loop() {
  // put your main code here, to run repeatedly:

  char key = keypad.getKey(); // recieves the pressed key.
  if (key) {
    Serial.println(key);
    ch[chcount++] = key;
    if (chcount == 4) {
      if (ch[0] == '1' && ch[1] == '2' && ch[2] == '3' && ch[3] == '4') {
        pass = true;
      }
    }
  }

  int sensorStatus = digitalRead(IRSensor);

  if (sensorStatus == 1) {
    digitalWrite(ledpin1, HIGH);
    
    if (pass) {
      lcd.setCursor(0, 0);
      lcd.print("Welcome");
    }else{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Intruder");
      tone(buzzer,1000); // send 1KHz sound signal, sound depends on frequency
     delay(1000); // delay
     noTone(buzzer); // stop sound..
     delay(1000);      
    }
  } else {
    digitalWrite(ledpin1, LOW);
  }
}
