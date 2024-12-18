#include <stdint.h>

struct Vector {
    int16_t x, y, z;
};

struct Game {
    uint8_t current_time, ticks, state;
};

extern void init_vector(struct Vector *vector);
extern struct Vector new_vector(int16_t x, int16_t y, int16_t z);

extern void init_game(struct Game *game);