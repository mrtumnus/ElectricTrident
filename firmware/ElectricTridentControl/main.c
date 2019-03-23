#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB = 0xFF; // PORTB is output, all pins
  PORTB = 0x00; // Make pins low to start

  for (;;) {
    PORTB ^= 0xFF; // invert all the pins
    _delay_ms(500); // wait some time
  }
  return 0;
}
