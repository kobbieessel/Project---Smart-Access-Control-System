#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Led.h>

// lcd
#define address 0x26
#define column 16
#define row 2

// pins
#define servoPin 11
#define buzzerPin 10
#define buttonPin 3
#define redPin 9
#define greenPin 6
#define bluePin 5

// Servo position
#define SERVO_CLOSE_DOOR_POSITION 170
#define SERVO_OPEN_DOOR_POSITION 70

byte buttonPrev;
byte newSate;

Servo servo;
LiquidCrystal_I2C lcd(address,column,row);
Led redLed(redPin);
Led greenLed(greenPin);
Led blueLed(bluePin);
unsigned long lastTimeRead;
unsigned long timeNow;
unsigned long threshold = 250;

void setup(){
  Serial.begin(115200);
  
  lcd.init();
  redLed.init();
  greenLed.init();
  blueLed.init();
  servo.attach(servoPin);
  
  pinMode(buttonPin,INPUT);
  servo.write(0);
  lcd.backlight();
  lastTimeRead = millis();
  buttonPrev = digitalRead(buttonPin);
  }

void loop(){
    // lcd
   lcd.setCursor(0,0);
   lcd.print("Push on button");
   lcd.setCursor(0,1);
   lcd.print("to call.");
   blueLed.on();

   
   timeNow = millis();
   if(timeNow - lastTimeRead >= threshold){
    newSate = digitalRead(buttonPin);
    
    if(newSate != buttonPrev){
      
      lastTimeRead = timeNow;
  
      if(newSate == LOW){
        lcd.clear();
        Serial.println("button_pressed");
        lcd.setCursor(0,0);
        lcd.print("Please wait a");
        lcd.setCursor(0,1);
        lcd.print("few seconds");
        delay(10000);
        lcd.clear();
        }
      }

   if(Serial.available() > 0){
          String cmd = Serial.readStringUntil('\n');
          // Access granted
          if(cmd == "open"){
            blueLed.off();
            greenLed.on();
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Door Open");
            
            for(int i =1; i < 3; i++){
            tone(buzzerPin,1000,300);
            delay(50);
            tone(buzzerPin,600,300);
            delay(50);
            }
            delay(1000);
            servo.write(SERVO_OPEN_DOOR_POSITION);
            delay(10000);
            servo.write(SERVO_CLOSE_DOOR_POSITION);
            greenLed.off();
            lcd.clear();
          }

         else if (cmd == "deny"){
          lcd.clear();
          blueLed.off();
          redLed.on();
          lcd.setCursor(0,0);
          lcd.print("Access denied");
          
          for(int i =1; i < 3; i++){
          tone(buzzerPin,600,300);
          delay(50);
          tone(buzzerPin,1000,300);
          delay(50);
          }
          delay(5000);
          redLed.off();
          lcd.clear();
          }
        }
    }
  }