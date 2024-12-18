#include <avr/io.h>

extern void init_display();
extern void clear_display();
extern void write_number_to_segment(uint8_t segment, uint8_t value);
extern void write_character_to_segment(uint8_t segment, char character);
extern void display_number(int number);
extern void display_string(char* string);
extern void display_string_and_wait(char* string, int delay);
extern void display_scrolling_string(char* string, int delay);