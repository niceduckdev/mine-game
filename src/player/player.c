#include <buttons.h>
#include <delay.h>
#include <level/level.h>
#include <player/player.h>
#include <tools.h>

#define START_X 6
#define START_Y 6
#define PLAYER_SPEED 2
#define BOMB_COUNT 25

// init player with starting coordinates
void init_player(struct Player *player) {
    player->x = START_X;
    player->y = START_Y;
    player->bomb_count = BOMB_COUNT;
    player->bombs_destroyed = 0;
}

// init input
void init_input(struct Input *input) {
    input->forward = 0;
    input->rotate = 0;
    input->bomb = 0;
}

// get input from buttons
volatile int button_1_was_pressed = 0;
volatile int button_2_was_pressed = 0;
void get_input(struct Input *input) {
    input->forward = button_is_pressed(0);

    if (button_is_pressed(1)) {
        button_1_was_pressed = 1;
    }
    else if (!button_is_pressed(1) && button_1_was_pressed) {
        button_1_was_pressed = 0;
        switch (input->rotate) {
            case 0:
                input->rotate = 1;
                break;
            case 1:
                input->rotate = 2;
                break;
            case 2:
                input->rotate = 3;
                break;
            case 3:
                input->rotate = 0;
                break;
            default:
                break;
        }
    }

    input->bomb = 0;
    if (button_is_pressed(2)) {
        button_2_was_pressed = 2;
    }
    else if (!button_is_pressed(2) && button_2_was_pressed) {
        button_2_was_pressed = 0;
        input->bomb = 1;
    }
}

// function to move the player in the direction they are facing
void handle_movement(struct Player *player, struct Input input) {
    // return if the player doesn't want to move
    if (input.forward <= 0) {
        return;
    }

    // move direction depending on current rotation
    switch (input.rotate) {
        case 0:
            player->y += (uint8_t)PLAYER_SPEED;
            break;
        case 1:
            player->x += (uint8_t)PLAYER_SPEED;
            break;
        case 2:
            player->y -= (uint8_t)PLAYER_SPEED;
            break;
        case 3:
            player->x -= (uint8_t)PLAYER_SPEED;
            break;
        default:
            break;
    }

    // stop the player if they are colliding
    struct Vector position = check_collisions(new_vector(player->x, player->y, 0));
    player->x = position.x;
    player->y = position.y;
}