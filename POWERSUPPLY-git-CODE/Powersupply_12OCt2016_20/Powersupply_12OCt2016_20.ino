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
byte place = 0; //0=millivolt,1=millivolt*10,2=millivolt*100,3=volt
//unsigned int  millivolts;
unsigned int i;
float  ovolts = 0.0000, volts = 0.0000 ;//, volts_10 = 0.0000, volts_100 = 0.0000 , volts_1000 = 0.0000;
void setup() {
  setupPWM16();
  lcdSetup();
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  place = 3; //init mode is volts
}

void loop() {

  if (digitalRead(4) == LOW) {
    place++;
    if (place == 4)place = 0;
  }
if (digitalRead(2) == LOW) {
  switch (place) {
    case 0 : volts += 0.001; break;
    case 1 : volts += 0.01; break;
    case 2 : volts += 0.1; break;
    case 3 : volts += 1; break;
  }
}

if (digitalRead(3) == LOW) {
  switch (place) {
    case 0 : volts -= 0.001; break;
    case 1 : volts -= 0.01; break;
    case 2 : volts -= 0.1; break;
    case 3 : volts -= 1; break;
  }
}

  ovolts = volts;
  lcd.clear();
  lcd.home();
  lcd.print(ovolts);
  Serial.println(ovolts);
  lcd.setCursor(8, 0);
  lcd.print(volts);
  lcd.setCursor(0, 1);
  lcd.print(place);
  delay(50);
}


