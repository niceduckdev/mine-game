#include <tools.h>

void init_vector(struct Vector *vector) {
    vector->x = 0;
    vector->y = 0;
    vector->z = 0;
}

struct Vector new_vector(int16_t x, int16_t y, int16_t z) {
	struct Vector vector;
    vector.x = x;
    vector.y = y;
    vector.z = z;
	return vector;
}

void init_game(struct Game *game) {
	game->current_time = 0;
	game->state = 0;
	game->ticks = 0;
}