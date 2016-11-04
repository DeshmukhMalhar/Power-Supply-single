//#define  TEST_on_MEGA
//#include <Key.h>
//#include <Keypad.h>
#include "IICLCDsetup.h"
#include "_16bitpwm.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/*
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
#ifdef TEST_on_MEGA
//keypadsetup(A0,A1,A2,A3,A7,A6,A5,A4);
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A7, A6, A5, A4};
#else
//keypadsetup(7,6,5,21,2,3,4,20);
byte rowPins[ROWS] = {7, 6, 5, 21};
byte colPins[COLS] = {2, 3, 4, 20};
#endif

//initialize an instance of class NewKeypad
Keypad Kpad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

*/
byte state_set = 0; //0=volt,1=millivolt,2=amp,3=milliamp
//unsigned int  millivolts;
float volts,millivolts;
void setup() {
  setupPWM16();
  lcdSetup();
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}

void loop() {
  if (state_set == 0) {
    if (digitalRead(2) == LOW) {
      volts++;
    }
    else if (digitalRead(3) == LOW) {
      volts--;
    }
    if (digitalRead(4) == LOW) {
      state_set++;
      if (state_set == 3)state_set = 0;
    }
  }
  else if (state_set == 1) {
    if (digitalRead(2) == LOW) {
      millivolts+=10;
      //volts = volts + (millivolts / 1000);
    }
    else if (digitalRead(3) == LOW) {
      millivolts-=10;
    }
    if (digitalRead(4) == LOW) {
      state_set++;
      //volts = volts + (millivolts / 1000);
      if (state_set == 2)state_set = 0;
    }
    //volts = volts + (millivolts / 1000);
  }
if(digitalRead(5)==0){volts = volts + (millivolts / 1000);}
 
  lcd.clear();
  lcd.home();
  lcd.print(volts);
  lcd.setCursor(0, 1);
  lcd.print(state_set);
  lcd.setCursor(6, 1);
  lcd.print(millivolts);
  delay(50);
}


