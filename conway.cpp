#include "conway_funcs.h"

int main(int argc, char **argv) {
    bool run_from_file_game = true;
    // Make this a switch

    if (run_from_file_game) {
        // Sample game using an input file.
        // Note that row and column size must be
        // given when initializing the game.
        ConwayGameOfLife game(8, 9, 100);
        game.import_from_file("light_spaceship.txt", 8, 9);
        //game.print_to_console_ = true;
        game.run_simulation();
        game.write_to_file();
    } else {
        // Game with specified board size and random
        // board population  
        ConwayGameOfLife game(30, 30, 500);
        game.print_to_console_ = false;
        game.populate();
        game.run_simulation();

        // Uncomment to write board evolution to file
        // Set print_to_console_ to false!
        game.write_to_file();
    }
}
