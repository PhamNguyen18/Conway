#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "conway_funcs.h"

int main(int argc, char **argv) {

    int c;
    int size = 0;
    int chance_living = 0;
    int generation = 0;
    ConwayGameOfLife game;
    game.populate(25);
    game.print_delay = 0.25;

    // Command line option error flags
    int unknown_flag = 0;
    int missing_flag = 0;

    while (1) {
        int option_index = 0;
        static struct option long_options[] =
        {
            {"size", required_argument, NULL, 's'},
            {"chance_living", required_argument, NULL, 'c'},
            {"generation", required_argument, NULL, 'g'}
        };

        c = getopt_long(argc, argv, ":s:c:g:", long_options, &option_index);
        // end point detection
        if (c == -1) {
            break;
        }
        switch(c) {
            case 's':
                size = std::stoi(optarg);
                game.size = size;
                break;
            case 'c':
                chance_living = std::stoi(optarg);
                game.empty_board();
                game.populate(chance_living);
                break;
            case 'g':
                generation = std::stoi(optarg);
                game.generation_stop = generation;
                break;
            case '?':
                std::printf("Unknown option: %c\n", optopt);
                unknown_flag = 1;
                break;
            case ':':
                std::printf("Missing arg for %c\n", optopt);
                missing_flag = 1;
                break;
        }
    }
    
    // Check to make sure there are no issues with command line options before starting game
    if (unknown_flag != 1 &&  missing_flag != 1) {
        game.run_simulation();
        std::cout << "Done!" << std::endl;
    }
}
