/*
 * Need to change some map functions for proper scaling at 10 and 20 volts
 * Need some logic to read current
 * Current amp is working properly
 * Maybe,A1 is fried
 * No changes were made to "IICLCDsetup.h" and "_16bitpwm.h"
 * Removed keyboard includes and variables
 * 
 */

#define DEBUG
//#define  TEST_on_MEGA
//#include <Key.h>
//#include <Keypad.h>
#include "IICLCDsetup.h"
#include "_16bitpwm.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

byte placeV = 0; //0=millivolt,1=millivolt*10,2=millivolt*100,3=volt
//unsigned int  millivolts;
unsigned int i, vwrt;
float  ovolts = 0.0000, volts = 0.0000, actVolts = 0.0000, iout = 0.0000 ,test=3.141592;
void setup() {
  setupPWM16();
  lcdSetup();
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  
  placeV = 3; //init mode is volts
  
  //Serial.println(test);
  //delay(5000);
}

void loop() {

  if (digitalRead(4) == LOW) {
    placeV++;
    if (placeV == 4)placeV = 0;
  }
  if (digitalRead(2) == LOW) {
    switch (placeV) {
      case 0 : volts += 0.001; break;
      case 1 : volts += 0.010; break;
      case 2 : volts += 0.100; break;
      case 3 : volts += 1.000; break;
    }
  }

  if (digitalRead(3) == LOW) {
    switch (placeV) {
      case 0 : volts -= 0.001; break;
      case 1 : volts -= 0.010; break;
      case 2 : volts -= 0.100; break;
      case 3 : volts -= 1.000; break;
    }
  }
  delay(50);
  //Put this in some sort of BlinkWithoutDelay loop


  ovolts = volts;
  ovolts = ovolts * 1000;
  vwrt = map(ovolts, 0, 5120, 0, 1023);
  analogWrite16(9, vwrt);

  lcd.clear();
  lcd.home();
#ifdef DEBUG
  /*Serial.println("\n");
  Serial.println("actVolts");
  Serial.println(actVolts);
  Serial.println("volts");
  Serial.println(volts);
  Serial.println("analogRead(A1)");
  Serial.println(analogRead(A1));
  Serial.println("iout");*/
  Serial.println(iout);
  //Serial.println("\n");

#endif
  actVolts = volts * 2;
  lcd.print(actVolts);
  lcd.setCursor(0, 1);
  lcd.print(placeV);
  lcd.setCursor(6, 0);
  iout = map(analogRead(A1), 0, 1023, 0, 5.1200);
  lcd.print(iout);


}


