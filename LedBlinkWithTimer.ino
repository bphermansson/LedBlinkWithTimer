// Arduino timer CTC interrupt example
// www.engblaze.com
// http://www.engblaze.com/microcontroller-tutorial-avr-and-arduino-timer-interrupts/
 
// avr-libc library includes
#include <avr/io.h>
#include <avr/interrupt.h>
 
#define LEDPIN 2
 
void setup()
{
    pinMode(LEDPIN, OUTPUT);
 
    // initialize Timer1
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

/*
 * For 1 second
 * (# timer counts + 1) = (target time) / (timer resolution)
 * (# timer counts + 1) = (1 s) / (6.4e-5 s)
 * (# timer counts + 1) = 15625
 * (# timer counts) = 15625 - 1 = 15624
 * 
 * 0.5 / 6.4e-5 = 7812,5
 * 
 */
 
    // set compare match register to desired timer count:
    OCR1A = 15624;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    sei();
}
 
void loop()
{
    // do some crazy stuff while my LED keeps blinking
}
 
ISR(TIMER1_COMPA_vect)
{
    digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}
