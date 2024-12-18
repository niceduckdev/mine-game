#include <avr/io.h>
#include <lights.h>

#define LIGHTS 4

void enable_light(short light) {
    if (light < 0 || light > (LIGHTS - 1)) {
        return;
    }

    DDRB |= (1 << (light + 2));
}

void enable_lights() {
    for (int i = 0; i < LIGHTS; i++) {
        enable_light(i);
    }

    set_lights(0);
}

// status -> 0 is off, 1 is on
void set_light(short light, short status) {
    if (light < 0 || light > (LIGHTS - 1)) {
        return;
    }

    if (status == 0) {
        PORTB |= (1 << (light + 2));
        return;
    }

    PORTB &= ~(1 << (light + 2));
}

void set_lights(short status) {
    for (int i = 0; i < LIGHTS; i++) {
        set_light(i, status);
    }
}

void set_light_dim(short light, int percentage, int duration) {
    for (int i = duration; i > 0; i -= 10) {
        set_light(light, 1);
        wait_ms(percentage / 10);
        set_light(light, 0);
        wait_ms((100 - percentage) / 10);
    }
}

void flicker_lights() {
    set_lights(1);
    wait_ms(100);
    set_lights(0);
    wait_ms(100);
}