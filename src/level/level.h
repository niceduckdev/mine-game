#include <stdint.h>

#define MAX_LEVEL 105
#define MIN_LEVEL 6
#define MINE_COUNT 15
#define MINE_RADIUS 3

extern void generate_mines();
extern struct Vector check_collisions(struct Vector position);
extern int8_t get_nearest_mine(struct Vector position);
extern uint8_t destroy_mine(uint8_t mine);