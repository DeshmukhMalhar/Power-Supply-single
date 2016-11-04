#define  TEST_on_MEGA
#include <Key.h>
#include <Keypad.h>
#include "IICLCDsetup.h"
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
//int vl, incomingByte, integerValue, ndgt, vl1, numbr, plc;
unsigned int integerValue = 0, recInt = 0, vl, prt = 0; // Max value is 65535
char incomingByte;
void setup() {
  lcdSetup();
  Serial.begin(115200);
}

void loop() {
  for (;;) {
    char customKey = Kpad.getKey();
    if (customKey) {
      integerValue = 0;
      while (1) {
        incomingByte = Kpad.getKey();
        if (incomingByte == 'D') break;
        if (incomingByte == 0) continue;
        integerValue *= 10;  // shift left 1 decimal place
        // convert ASCII to integer, add, and shift left 1 decimal place
        integerValue = ((incomingByte - 48) + integerValue);
      }

    }
    vl = integerValue;
    if (vl > 0) {
      prt = 1; 
           
      break;
    }
  }
//#ifdef DEBUG
  if (prt == 1) {
    //lcd.clear();
    lcd.print(vl);
    Serial.println(vl);
    prt = 0;
    vl=0;
  }
//#endif

}
