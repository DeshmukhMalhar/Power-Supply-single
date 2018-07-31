#define  TEST_on_MEGA
#include <Key.h>
#include <Keypad.h>
#include "IICLCDsetup.h"
#include "_16bitpwm.h"
//#include "CustomKeypad.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
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


float realV, realI, setV, setI;
byte state_set = 0; //1=volt,2=millivolt,3=amp,4=milliamp
int vl, vo, incomingByte, integerValue, ndgt, vl1, numbr, it, volt, millivolt;
void setup() {
  setupPWM16();
  lcdSetup();
  Serial.begin(115200);
}

void loop() {
char customKey;
  switch (state_set) {
    case 1 :
       customKey= Kpad.getKey();
      if (customKey) {
        Serial.println(customKey);
        lcd.home();
        lcd.print(customKey);

        if ('0' <= customKey && '9' >= customKey) {
          while (customKey != 'D') {
            vl = customKey - '0';
            customKey = Kpad.getKey();
            numbr *= 10;
            numbr = ((customKey - '0') + numbr);
            volt = numbr;
          }
        }
      }
      break;
    case 2:
       customKey = Kpad.getKey();
      if (customKey) {
        Serial.println(customKey);
        lcd.home();
        lcd.print(customKey);

        if ('0' <= customKey && '9' >= customKey) {
          while (customKey != 'D') {
            vl = customKey - '0';
            customKey = Kpad.getKey();
            numbr *= 10;
            numbr = ((customKey - '0') + numbr);
            millivolt = numbr;
          }
        }
      }
      break;
  }
  vo = volt + (millivolt / 1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(vo);

}


