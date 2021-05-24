#include "conway_funcs.h"

int main(int argc, char **argv) {
    // Sample game using an input file
    ConwayGameOfLife game;
    game.import_from_file("oscillator_test.txt", 5);

    // Game with specified board size and randomly
    // generating a board
    //ConwayGameOfLife game(22, 500);
    //game.populate(25);
    
    game.print_delay = 0.25;
    game.run_simulation();
}
