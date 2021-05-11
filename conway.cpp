#include<iostream>
using std::cout; using std::endl; using std::cin;
#include "conway_funcs.h"

int main(int, char **argv) {
    // Sample game
    ConwayGameOfLife game(22, 500);
    game.populate(25);
    game.print_delay = 0.25;
    game.run_simulation();
}
