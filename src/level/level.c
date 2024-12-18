#include <level/level.h>
#include <meter.h>
#include <stdint.h>
#include <stdio.h>
#include <tools.h>

struct Vector mines[MINE_COUNT];

// function to generate all of the mines and their positions
void generate_mines() {
    // we get the seed from the meter
    srand(get_meter_value());

    for (int i = 0; i < MINE_COUNT; i++) {
        mines[i].x = rand() % (100 + 1 - 0) + 0;  // x position
        mines[i].y = rand() % (100 + 1 - 0) + 0;  // y position
        mines[i].z = 0;                           // 0 is active, 1 is destroyed
    }
}

// function to limit the player to the level
struct Vector check_collisions(struct Vector position) {
    if (position.x >= (uint8_t)MAX_LEVEL) {
        position.x = (uint8_t)MAX_LEVEL;
    }
    if (position.y >= (uint8_t)MAX_LEVEL) {
        position.y = (uint8_t)MAX_LEVEL;
    }
    if (position.x <= (uint8_t)MIN_LEVEL) {
        position.x = (uint8_t)MIN_LEVEL;
    }
    if (position.y <= (uint8_t)MIN_LEVEL) {
        position.y = (uint8_t)MIN_LEVEL;
    }

    return position;
}

// function to check if the player is near a mine
// returns an index if they are and -1 if they are not
int8_t get_nearest_mine(struct Vector position) {
    for (int i = 0; i < MINE_COUNT; i++) {
        if (position.x >= mines[i].x - MINE_RADIUS && position.x <= mines[i].x + MINE_RADIUS && position.y >= mines[i].y - MINE_RADIUS && position.y <= mines[i].y + MINE_RADIUS && !mines[i].z) {
            return i;
        }
    }

    return -1;
}

// destroys a mine using the index
uint8_t destroy_mine(uint8_t mine) {
    if (mines[mine].z == 1 || mine == -1) {
        return 0;
    }

    mines[mine].z = 1;
    return 1;
}