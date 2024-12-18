#include "display.h"

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#define NUMBER_OF_SEGMENTS 8
#define NUMBER_OF_DISPLAYS 4

const uint8_t SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99,
                               0x92, 0x82, 0xF8, 0X80, 0X90};
const uint8_t ALPHABET_MAP[] = {0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0xC2,
                                0x89, 0xCF, 0xE1, 0x8A, 0xC7, 0xEA, 0xC8,
                                0xC0, 0x8C, 0x4A, 0xCC, 0x92, 0x87, 0xC1,
                                0xC1, 0xD5, 0x89, 0x91, 0xA4, 0xFF};
const uint8_t SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

void init_display() {
    DDRD |= _BV(PD4);
    DDRD |= _BV(PD7);
    DDRB |= _BV(PB0);
}

void clear_display() {
	display_string("   ");
}

void shift(uint8_t value, uint8_t bit_order) {
    uint8_t bit;

    for (uint8_t i = 0; i < NUMBER_OF_SEGMENTS; i++) {
        if (bit_order == 0) {
            bit = !!(value & (1 << i));
        }
        else {
            bit = !!(value & (1 << (7 - i)));
        }

        if (bit == 1) {
            PORTB |= _BV(PB0);
        }
        else {
            PORTB &= ~_BV(PB0);
        }

        PORTD |= _BV(PD7);
        PORTD &= ~_BV(PD7);
    }
}

void write_number_to_segment(uint8_t segment, uint8_t value) {
    PORTD |= _BV(PD4);
    shift(SEGMENT_MAP[value], 1);
    shift(SEGMENT_SELECT[segment], 1);
    PORTD &= ~_BV(PD4);
}

void write_character_to_segment(uint8_t segment, char character) {
    if (character == ' ') {
        PORTD |= _BV(PD4);
        shift(0XFF, 1);
        shift(SEGMENT_SELECT[segment], 1);
        PORTD &= ~_BV(PD4);
        return;
    }

    if (!isalnum(character)) {
        PORTD |= _BV(PD4);
        shift(0XFF, 1);
        shift(SEGMENT_SELECT[segment], 1);
        PORTD &= ~_BV(PD4);
        return;
    }

    if (islower(character)) {
        character = character - 32;
    }

    PORTD |= _BV(PD4);
    shift(ALPHABET_MAP[character - 65], 1);
    shift(SEGMENT_SELECT[segment], 1);
    PORTD &= ~_BV(PD4);
}

void display_number(int number) {
    if (number < 0 || number > 9999) {
        return;
    }

    write_number_to_segment(0, number / 1000);
    write_number_to_segment(1, (number / 100) % 10);
    write_number_to_segment(2, (number / 10) % 10);
    write_number_to_segment(3, number % 10);
}

void display_string(char* string) {
    if (strlen(string) < 0 || strlen(string) > 4) {
        return;
    }

    for (int i = 0; i < 4; i++) {
        write_character_to_segment(i, string[i]);
    }
}

void display_string_and_wait(char* string, int delay) {
    if (strlen(string) < 0 || strlen(string) > 4) {
        return;
    }

    write_character_to_segment(0, string[0]);
    wait_ms(delay);
    write_character_to_segment(1, string[1]);
    wait_ms(delay);
    write_character_to_segment(2, string[2]);
    wait_ms(delay);
    write_character_to_segment(3, string[3]);
    wait_ms(delay);
}

void display_scrolling_string(char* string, int delay) {
    int length = 0;
    char character = string[0];
    while (character != '\0') {
        length++;
        character = string[length];
    }
    if (length <= NUMBER_OF_DISPLAYS) {
        display_string_and_wait(string, delay);
    }
    else {
        int lower = 0;
        char* subStr = malloc(NUMBER_OF_DISPLAYS * sizeof(char));
        while (lower + NUMBER_OF_DISPLAYS <= length) {
            for (int i = 0; i < NUMBER_OF_DISPLAYS; i++) {
                subStr[i] = string[lower + i];
            }
            display_string_and_wait(subStr, delay / (length + 1 - NUMBER_OF_DISPLAYS));
            lower++;
        }
    }
}