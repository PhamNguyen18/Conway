#include "conway_funcs.h"

int main(int argc, char **argv) {
    // Sample game using an input file
    //ConwayGameOfLife game;
    //game.import_from_file("light_spaceship.txt", 8, 9);

    // Game with specified board size and randomly
    // generating a board
    ConwayGameOfLife game;
    game.save_history_ = true;
    game.print_to_console_ = false;
    //game.print_to_console_delay_ = 0.5;

    game.populate();
    //game.view_board();
    
    game.run_simulation();
    game.write_to_file();
}
