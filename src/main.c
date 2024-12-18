#include <beep.h>
#include <buttons.h>
#include <debug.h>
#include <delay.h>
#include <display.h>
#include <lights.h>
#include <math.h>
#include <timer.h>
#include <tools.h>

#include "level/level.h"
#include "player/player.h"

#define TICK_DELAY 50
#define TIME 60

struct Player player;
struct Game game;

// function that adds 2 to the current game.ticks every cpu pulse,
// holds the time that the player has left to destroy all the mines
void tick() {
    if (game.state != 1) {
        return;
    }

    write_number_to_segment(0, ((player.x - MIN_LEVEL) / 10) % 10);
    write_number_to_segment(1, (player.x - MIN_LEVEL) % 10);
    write_number_to_segment(2, ((player.y - MIN_LEVEL) / 10) % 10);
    write_number_to_segment(3, (player.y - MIN_LEVEL) % 10);

    if (game.current_time >= TIME || player.bomb_count <= 0) {
        game.state = 2;
        return;
    }

    switch (game.current_time) {
        case TIME / 4:
            set_light(0, 1);
            set_light(1, 0);
            set_light(2, 0);
            set_light(3, 0);
            break;
        case (TIME / 4) * 2:
            set_light(0, 1);
            set_light(1, 1);
            set_light(2, 0);
            set_light(3, 0);
            break;
        case (TIME / 4) * 3:
            set_light(0, 1);
            set_light(1, 1);
            set_light(2, 1);
            set_light(3, 0);
            break;
        case (TIME / 4) * 4:
            set_light(0, 1);
            set_light(1, 1);
            set_light(2, 1);
            set_light(3, 1);
            break;
        default:
            break;
    }

    game.ticks += 1;

    if (game.ticks > 100) {
        game.current_time++;
        game.ticks = 0;
    }
}

// function that is called when the game loads
void start() {
    // init the debugger, buttons, lights and display
    init_debugger();
    enable_lights();
    enable_buttons();
    init_display();
    init_timer();
    init_beep();

    // init the game, player, input and generate the list of mines
    init_game(&game);
    init_player(&player);
    init_input(&input);
    generate_mines();
    clear_display();

    // print tutorial in the serial output
    println("Druk op knop 1 om het spel te starten!");
}

// run tick() on every tick from the cpu
ISR(TIMER0_COMPA_vect) {
    tick();
}
ISR(TIMER0_OVF_vect) {
    tick();
}

// function that is called every tick
// (with a tick delay of TICK_DELAY)
void update() {
    switch (game.state) {
        // player is in lobby
        case 0:
            if (button_is_pressed(0)) {
                game.state = 1;
            }

            flicker_lights();
            break;

        // player is running game
        case 1:
            // get input from the buttons
            get_input(&input);

            // move player
            handle_movement(&player, input);

            // check if near mine
            if (get_nearest_mine(new_vector(player.x, player.y, 0)) != -1) {
                play_beep();
            }

            // destroy nearest mine if player pressed button 3
            if (input.bomb && player.bomb_count > 0) {
                if (destroy_mine(get_nearest_mine(new_vector(player.x, player.y, 0)))) {
                    player.bomb_count--;
                    player.bombs_destroyed++;
                }
            }
            break;

        // player has run out of time
        case 2:
            write_character_to_segment(0, 'B');
            write_number_to_segment(1, (player.bombs_destroyed / 100) % 10);
            write_number_to_segment(2, (player.bombs_destroyed / 10) % 10);
            write_number_to_segment(3, player.bombs_destroyed % 10);

            // print einde in the serial output
            if (player.bombs_destroyed == 0) {
                printf("Je stelt je vaderland teleur.\n");
            }
            else if (player.bombs_destroyed > 0 && player.bombs_destroyed <= 10) {
                printf("Goed gedaan! Je hebt het vaderland een beetje veiliger gemaakt.\n");
            }
            else {
                printf("Het vaderland is trots! Goed gedaan! Je hebt alle mijnen onschadelijk gemaakt.\n");
            }
            break;

        default:
            break;
    }
}

// main entry function
int main() {
    start();

    while (1) {
        update();
        if (game.state == 1) {
            wait_ms(TICK_DELAY);
        }
    }

    return 0;
}