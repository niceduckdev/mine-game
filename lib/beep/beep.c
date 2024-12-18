#include <avr/io.h>
#include <delay.h>

void init_beep() {
    DDRD |= (1 << PD3);
	PORTD |= (1 << PD3);
}

void play_beep() {
    PORTD &= ~(1 << PD3);
    wait_us(3000);
    PORTD |= (1 << PD3);
    wait_us(3000);
}

void play_loud_beep() {
    PORTD &= ~(1 << PD3);
    wait_us(500);
    PORTD |= (1 << PD3);
    wait_us(500);
}