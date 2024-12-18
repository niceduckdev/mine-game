#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

void wait_ms(int miliseconds) { _delay_ms(miliseconds); }

void wait_us(int microseconds) { _delay_us(microseconds); }