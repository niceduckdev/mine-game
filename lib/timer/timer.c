#include "timer.h"

void init_timer() {
	TCCR0A |= _BV(WGM00) | _BV(WGM01);
    TCCR0B |= _BV(CS02) | _BV(CS00);

    TIMSK0 |= _BV(TOIE0);
    TIMSK0 |= _BV(OCIE0A);
    sei();
}