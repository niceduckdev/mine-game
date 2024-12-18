/* Functions to initialize, send, receive over USART

   initUSART requires BAUD to be defined in order to calculate
     the bit-rate multiplier.
 */
#include <stdio.h>

#ifndef BAUD      /* if not defined in Makefile... */
#define BAUD 9600 /* set a safe default baud rate */
#endif

#define USART_HAS_DATA bit_is_set(UCSR0A, RXC0)
#define USART_READY bit_is_set(UCSR0A, UDRE0)

/* Takes the defined BAUD and F_CPU,
   calculates the bit-clock multiplier,
   and configures the hardware USART                   */
void init_debugger(void);

int transmit_character(char character, FILE* stream);

/* Blocking transmit and receive functions.
   When you call receiveByte() your program will hang until
   data comes through.  We'll improve on this later. */
void transmit_byte(uint8_t data);
uint8_t receive_byte(void);

void print_string(const char myString[]);
/* Utility function to transmit an entire string from RAM */
void read_string(char myString[], uint8_t maxLength);
/* Define a string variable, pass it to this function
   The string will contain whatever you typed over serial */

void print_byte(uint8_t byte);
/* Prints a byte out as its 3-digit ascii equivalent */
void print_word(uint16_t word);
/* Prints a word (16-bits) out as its 5-digit ascii equivalent */

void print_binary_byte(uint8_t byte);
/* Prints a byte out in 1s and 0s */
char nibble_to_hex(uint8_t nibble);
char nibble_to_hex_character(uint8_t nibble);
void print_hex_byte(uint8_t byte);
/* Prints a byte out in hexadecimal */
uint8_t get_number(void);
/* takes in up to three ascii digits,
 converts them to a byte when press enter */

extern void println(char* string);