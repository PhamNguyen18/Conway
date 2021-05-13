# Conway

This repository contains a simple implementation of Conway's Game of Life. The Game of Life uses a simple set of rules to evolve an initial state without further user input. This initial state takes the form of a 2D board with each element containing either a living "cell" or a dead "cell". Higher dimensional boards are also possible. The board is updated according to the follow rules based on the state of the surround neighbors for each living or dead cell: 

* A living cell will survive if it has two or three living neighbors
* A living cell with any other number of living neighbors will die 
* A cell is produced in place of a dead cell if there are exactly three living neighbors

For neighbors that lay outside the board, the code will "wrap around" and check the neighbor on the exact opposite side of the board. As noted previously, the implementation of the Game of Life in this repository is simple in that every cell whether dead or alive is checked every generation as the board evolves. This can be rather inefficient for large boards with lots of dead cells, and there are many potential ways to improve performance which will be explored in the future. 

For more details see the [Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) entry.

TODO:
* Allow users to import their own boards to initialize the game
* Allow users to save boards to file
* Explore performance improvements

