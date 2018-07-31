#define IICLCDsetup.h 

/*IIC LCD 16X2 test example
 * Connect the IIC LCD as follows
 * IIC LCD      ARDUINO
 * +5V            +5V
 * GND            GND
 * SCL            SCL
 * SDA            SDA
 *
 * by Malhar Deshmukh
 * 11APR2016
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR    0x27 // <<-- Add your address here.Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

void lcdSetup() {
  lcd.begin (16, 2); //  LCD is 16 characters x 2 lines
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);  // Switch on the backlight
  lcd.clear();
  //Uncomment this to test the function
  /*
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("0123456789ABCDEF");
  lcd.setCursor(0, 1);
  lcd.print("Test Passed");
  */
}



