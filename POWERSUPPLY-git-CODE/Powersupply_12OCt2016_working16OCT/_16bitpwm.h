#define _16bitpwm
//#define ARDUINO_MEGA     //Timers and Digital pins are differnt on different boards
void setupPWM16() {
  TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
           | _BV(WGM11);                   /* mode 14: fast PWM, TOP=ICR1 */
  TCCR1B = _BV(WGM13) | _BV(WGM12)
           | _BV(CS11);                    /* prescaler 1 */
  ICR1 = 0x03ff;                      /* TOP counter value (freeing OCR1A*/

  /*
   * for 10 bit , set as 0x03ff,confirmed-MALHAR
   * frequency= 15.625KHz for 16Mhz CPU clock
   * frequency=  7.812KHz for 8Mhz CPU clock
  */

  /*
  * Comments about the setup
  * Changing ICR1 will effect the amount of bits of resolution.
  * ICR1 = 0xffff; (65535) 16-bit resolution
  * ICR1 = 0x7FFF; (32767) 15-bit resolution
  * ICR1 = 0x3FFF; (16383) 14-bit resolution etc....

  * Changing the prescaler will effect the frequency of the PWM signal.
  * Frequency[Hz}=CPU/(ICR1+1) where in this case CPU=16 MHz
  * 16-bit PWM will be>>> 16000000/(65535+1)=244.14Hz
  */

#ifndef TEST_on_MEGA
  DDRB |= _BV(PB1) | _BV(PB2);
#endif

#ifdef TEST_on_MEGA
  DDRB |= _BV(PB5) | _BV(PB6) | _BV(PB7) ;
#endif
}
void analogWrite16(uint8_t pin, int val)
{
  switch (pin) {
    case 9: OCR1A = val; break;
    case 10: OCR1B = val; break;
#ifdef TEST_on_MEGA
    case 11: OCR1A = val; break;
    case 12: OCR1B = val; break;
    case 13: OCR1C = val; break;
#endif
  }
}
