#include <stdint.h>

struct Player {
	uint8_t x, y, bomb_count, bombs_destroyed;
};

struct Input {
	uint8_t forward, rotate, bomb;
};

struct Input input;

extern void init_player(struct Player *player);
extern void init_input(struct Input *input);
extern void get_input(struct Input *input);
extern void handle_movement(struct Player *player, struct Input input);