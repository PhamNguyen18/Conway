#include<unistd.h>
#include<random>
#include<fstream>
#include<iostream>
#include<stdexcept>
#include<string>
using std::string;
#include<vector>
using std::vector;

#include "conway_funcs.h"

using BoardRow = vector<unsigned int>;
using Board = vector<BoardRow>;

unsigned int ConwayGameOfLife::get_cell(const Board &board, long row, long col) {
    // Allows for wrap around behavior for neighbors outside of board limits
    if (row < 0)
        row = size - 1;
    if (row == size)
        row = 0;
    if (col < 0)
        col = size - 1;
    if (col == size)
        col = 0;

    return board[row][col];
}


void ConwayGameOfLife::set_cell(Board &board, long row, long col, unsigned int value) {
    if (value == 0 || value == 1) {
        board[row][col] = value;
    } else {
        throw std::range_error("Value must be 0 or 1");
    }
}

unsigned int ConwayGameOfLife::count_neighbors(const Board &board, long row, long col) {
    unsigned int living_cells = 0;
    for (auto pos : neighbors) {
        if (get_cell(board, row + pos[0], col + pos[1])) {
            living_cells++;
        } else {
            continue;
        }
    }
    return living_cells;
}

void ConwayGameOfLife::update_board(const Board &current_board, Board &next_board,
                                    long row, long col) {
    // Number of neighbors determines if current cell is alive, dead, or
    // created in the next generation
    unsigned int num_neighbors = count_neighbors(current_board, row, col);
    if (current_board[row][col]) {
        if (num_neighbors < 2) {
            set_cell(next_board, row, col, 0);
        } else if (num_neighbors == 2 || num_neighbors == 3) {
            set_cell(next_board, row, col, 1);
        } else if (num_neighbors > 3) {
            set_cell(next_board, row, col, 0);
        }
    } else {
        if (num_neighbors == 3) {
            set_cell(next_board, row, col, 1);
        }
    }
}

void ConwayGameOfLife::populate(long chance_to_live, long seed) {
    // Each element on board has a chance to create a living cell
    // during initialization. Chance to live is between 1-100.
    Board& board = current_board;

    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(1, 100);

    for (int row=0; row < size; ++row) {
        for (int col=0; col < size; ++col) {
            bool is_living = dist(gen) <= chance_to_live;
            if (is_living) {
                set_cell(board, row, col, 1);
            } else {
                continue;
            }
        }
    }
}

void ConwayGameOfLife::swap_boards(Board &current_board, Board &next_board) {
    current_board = next_board;
}

void ConwayGameOfLife::run_simulation(void) {
    // Needed to keep board displayed longer in console
    int microsecond = 1000000;

    // Play the game
    while (generation <= generation_stop) {
        std::cout << "Generation: " << generation << std::endl;
        print_board(current_board);
        usleep(microsecond * print_delay);
        for (int row=0; row < size; ++row) {
            for (int col=0; col < size; ++col) {
                update_board(current_board, next_board, row, col);
            }
        }
        swap_boards(current_board, next_board);
        generation++;
    }
}

void ConwayGameOfLife::import_from_file(string file, long import_size) {
    // Allows for user provided board to be imported
    size = import_size;
    std::ifstream input(file);

    while (!input.eof()) {
        for (int i=0; i<size; ++i) {
            for (int j=0; j<size; ++j) {
                input >> current_board[i][j];
            }
        }
    }
    input.close();
}

void ConwayGameOfLife::print_board(const Board &board) {
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void ConwayGameOfLife::write_to_file(void) {
    // Writes each board generation to file (or every nth generation etc)
}
