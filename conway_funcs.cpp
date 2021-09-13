#include<unistd.h>
#include<algorithm>
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

unsigned int ConwayGameOfLife::get_cell(long row, long col) {
    // Allows for wrap around behavior for neighbors outside of board limits
    if (row < 0)
        row = row_ - 1;
    else if (row == row_)
        row = 0;
    if (col < 0)
        col = col_ - 1;
    else if (col == col_)
        col = 0;

    return current_board_[row][col];
}


void ConwayGameOfLife::set_cell(long row, long col, unsigned int value) {
    if (value == 0 || value == 1) {
        current_board_[row][col] = value;
    } else {
        throw std::range_error("Value must be 0 or 1");
    }
}

unsigned int ConwayGameOfLife::count_neighbors(long row, long col) {
    unsigned int living_cells = 0;
    for (auto pos : neighbors) {
        if (get_cell(row + pos[0], col + pos[1])) {
            living_cells++;
        } else {
            continue;
        }
    }
    return living_cells;
}

void ConwayGameOfLife::update_board(long row, long col) {
    // Number of neighbors determines if current cell is alive, dead, or
    // created in the next generation
    unsigned int num_neighbors = count_neighbors(row, col);
    if (current_board_[row][col]) {
        if (num_neighbors < 2) {
            next_board_[row][col] = 0;
        } else if (num_neighbors == 2 || num_neighbors == 3) {
            next_board_[row][col] = 1;
        } else if (num_neighbors > 3) {
            next_board_[row][col] = 0;
        }
    } else {
        if (num_neighbors == 3) {
            next_board_[row][col] = 1;
        }
    }
}

void ConwayGameOfLife::populate(long chance_to_live, long seed) {
    // Each element on board has a chance to create a living cell
    // during initialization. Chance to live is between 1-99.

    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(1, 100);

    if (chance_to_live >= 0 && chance_to_live <= 100) {
        for (int row=0; row < row_; ++row) {
            for (int col=0; col < col_; ++col) {
                bool is_living = (dist(gen) <= chance_to_live);
                if (is_living) {
                    set_cell(row, col, 1);
                } else {
                    continue;
                }
            }
        }
    } else {
        throw std::out_of_range("Chance to live should be between 0 and 100!");
    }
}

void ConwayGameOfLife::empty_board (void) {
    // Set all board elements to dead (0) cells
    Board& board = current_board_;

    for (auto& row : board) {
        std::fill(row.begin(), row.end(), 0);
    }
}

void ConwayGameOfLife::swap_boards(Board &current_board_, Board &next_board_) {
    current_board_ = next_board_;
}

void ConwayGameOfLife::run_simulation(void) {
    // Needed to keep board displayed longer in console
    int microsecond = 1000000;

    // Play the game
    while (generation_ <= generation_stop_) {
        if (print_to_console_) {
            view_board(); // current_board_
            usleep(microsecond * print_delay_);
        }

        if (save_history_) {
            game_history_[generation_] = current_board_;
        }

        for (int row=0; row < row_; ++row) {
            for (int col=0; col < col_; ++col) {
                update_board(row, col);
            }
        }

        swap_boards(current_board_, next_board_);
        generation_++;
    }
}

void ConwayGameOfLife::import_from_file(string file, long row, long col) {
    // Allows user to import their own board 
    // TODO: Auto detect dimensions from file
    std::ifstream input(file);
    row_ = row;
    col_ = col;

    while (!input.eof()) {
        for (int row = 0; row < row_; ++row) {
            for (int col = 0; col < col_; ++col) {
                input >> current_board_[row][col];
            }
        }
    }
    input.close();
}

void ConwayGameOfLife::view_board(long generation) {
    // Either prints the current board or a user specified generation
    Board &board = current_board_;
    long generation_print = generation_;

    if (generation >= 0) {
        board = game_history_[generation];
        generation_print = generation;
    }

    std::cout << "Generation: " << generation_print << std::endl;
    for (int row = 0; row < row_; ++row) {
        for (int col = 0; col < col_; ++col) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void ConwayGameOfLife::write_to_file(void) {
    // Writes each board generation to file 
    std::ofstream out_file;
    out_file.open(out_file_name_);
    out_file << row_ << "," << col_ << "," << generation_stop_ << "\n";
 
    for (const auto& get_pair : game_history_) {
        out_file << get_pair.first << ',';
        for (const auto& row : get_pair.second) {
            for (const auto& e : row) {
                out_file << e << ',';
            }
        }
        out_file << '\n';
    }
 
    out_file.close();
}
