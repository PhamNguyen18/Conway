#include "conway_funcs.h"

int main(int argc, char **argv) {
    // Sample game using an input file
    //ConwayGameOfLife game;
    //game.import_from_file("oscillator_test.txt", 5);

    // Game with specified board size and randomly
    // generating a board
    ConwayGameOfLife game(20, 500); 
    game.populate(20);
    
    game.print_delay_ = 0.25;
    game.print_to_console_ = true;
    game.run_simulation();
}
