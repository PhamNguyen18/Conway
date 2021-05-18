#ifndef CONWAY_CONWAY_FUNCS_H_
#define CONWAY_CONWAY_FUNCS_H_

/*
  Author: Pham Nguyen
  Last Update: 5-6-21

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

  TODO:
    * Figure out how to write to file
    * What file format? (csv?)
    * Try some optimiziations (i.e. buffers)
*/ 

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
      long generation = 1;
      // "Filter" to check if neighbors exist on the board
      vector<vector<int>> neighbors{{-1, -1}, {-1, 0}, {-1, 1},
                                    {0, -1}, {0, 1},
                                    {1, -1}, {1, 0}, {1, 1}};
      
      // Helper methods
      unsigned int get_cell(const Board &board, long row, long col);
      unsigned int count_neighbors(const Board &board, long row, long col);
      void update_board(const Board &board, Board &next_board, long row, long col);
      void swap_boards(Board &current_board, Board &next_board);

  public:
      long size = 20;
      long generation_stop = 500;
      double print_delay = 0.2;

      ConwayGameOfLife() = default;
      ConwayGameOfLife(long s, long gen_stop) : size(s), generation_stop(gen_stop) {}
      Board current_board = Board(size, BoardRow(size, 0));
      Board next_board = Board(size, BoardRow(size, 0));

      void set_cell(Board &board, long row, long col, unsigned int value);
      void populate(long chance_to_live = 10, long seed = 8675309); 
      void run_simulation(void);

      // Utilities
      void import_from_file(string file, long import_size);
      void print_board(const Board &board);
      void write_to_file(void);
};

#endif  // CONWAY_CONWAY_FUNCS_H_
