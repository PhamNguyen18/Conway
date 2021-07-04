#ifndef CONWAY_CONWAY_FUNCS_H_
#define CONWAY_CONWAY_FUNCS_H_

/*
  Author: Pham Nguyen
  Last Update: 7-02-21

  A naive implement of Conway's Game of
  Life. The game is initialized with two
  vectors with each element repesenting a
  "cell" that is either dead (0) or alive (1).
  The first vector represents the current
  state of the game and the second a 
  successor state. 

  The rules for evolving the board are
  as follows: 
    * A cell with < 2 neighbors dies 
    * A cell with 2 or 3 neighors lives
    * A cell with > 3 dies
    * A dead cell with exact 3 neighors
      creates a new living cell

  For cells at the edge of the board,
  periodic boardary conditions are used.
  That is, the neighors of a cell on the
  left edge of the board (for example)
  include those on the far right edge
  of the board. 

  TO DO:
    - Convert to 1D vectors (need to change indexing)
    - Finish output file method (easier onces in 1D)
*/ 

#include<map>
#include<sstream>
using std::ostringstream;
#include<string>
using std::string;
#include<vector>
using std::vector;

using BoardRow = vector<unsigned int>;
using Board = vector<BoardRow>;

class ConwayGameOfLife {
  private:
      long generation_ = 1;
      std::map<long, Board> game_history_; // Map of each generation
      // "Filter" to check if neighbors exist on the board
      vector<vector<int>> neighbors{{-1, -1}, {-1, 0}, {-1, 1},
                                    {0, -1}, {0, 1},
                                    {1, -1}, {1, 0}, {1, 1}};
      
      // Helper methods
      unsigned int get_cell(long row, long col);
      unsigned int count_neighbors(long row, long col);
      void update_board(long row, long col);
      void swap_boards(Board &current_board, Board &next_board);

  public:
      // Output options and game history settings
      bool save_history_ = true; // Save boards to a map 
      bool print_to_console_ = false;
      double print_delay_ = 0.2;
      string out_file_name_ = "game_out.txt"; 

      // Game parameters
      long size_ = 20;
      long generation_stop_ = 500;

      ConwayGameOfLife() = default;
      ConwayGameOfLife(long s, long gen_stop) : size_(s), generation_stop_(gen_stop) {}
      Board current_board_ = Board(size_, BoardRow(size_, 0)); 
      Board next_board_ = Board(size_, BoardRow(size_, 0)); 

      // Core game methods
      void set_cell(long row, long col, unsigned int value);
      void populate(long chance_to_live = 20, long seed = 8675309); 
      void empty_board(void);
      void run_simulation(void);

      // Utilities
      void print_board(long generation = -1); 
      void import_from_file(string file, long import_size);
      void write_to_file(void);
};

#endif  // CONWAY_CONWAY_FUNCS_H_
