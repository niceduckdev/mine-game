#include <avr/interrupt.h>
#include <avr/io.h>
#include <buttons.h>

#define BUTTONS 3

void init_button_interrupts() {
    PCICR |= _BV(PCIE1);
    PCMSK1 |= (1 << 1);
    sei();
}

void enable_button(int button) { DDRC &= ~(1 << (button + 1)); }

void enable_buttons() {
    for (int i = 0; i < BUTTONS; i++) {
        enable_button(i);
    }
}

int button_is_pressed(int button) {
    if ((PINC & (1 << (button + 1))) == 0) {
        return 1;
    }

    return 0;
}