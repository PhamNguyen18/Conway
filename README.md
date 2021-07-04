# Conway

Introduction
------------
This repository contains a simple implementation of Conway's Game of Life. The Game of Life uses a simple set of rules to evolve an initial state without further user input. This initial state takes the form of a 2D board with each element containing either a living "cell" or a dead "cell". [Higher dimensional](https://github.com/bruzewskis/HyperLife)  boards are also possible. The board is updated according to the following rules based on the state of the surround neighbors for each living or dead cell: 

* A living cell will survive if it has two or three living neighbors
* A living cell with any other number of living neighbors will die 
* A cell is produced in place of a dead cell if there are exactly three living neighbors

For neighbors that lay outside the board, the code will "wrap around" and check the neighbor on the exact opposite side of the board. As noted previously, the implementation of the Game of Life in this repository is simple in that every cell whether dead or alive is checked every generation as the board evolves. This can be rather inefficient for large boards with lots of dead cells, and there are many potential ways to improve performance which will be explored in the future. 

For more details see the [Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) entry.

Usage
-----
The Game of Life can be played using either the command line or by creating an instance of the game in a separate file (see `ex_manual_conway.cpp` for an example). 

| :warning: WARNING          |
|:---------------------------|
| The command line interface does not currently work |

### Command Line
* `-s`, `--size`       :  Specifies the number of elements per side of the board.
* `-c`, `--chance_living`  : The percent chance that an element on the board will contain a living cell during initialization. Must be an integer between 1 and 100, passed to the `populate` method. 
* `-g`, `--generation`        : The number of generations to evolve the board for.  

If no options are passed, a game will be played using default settings:
* size = 20
* chance_living = 25
* generation = 500

### Manual Setup
Since the board evolves on its own, the user only has direct control over the initial conditions of the game. A game can be initialized by specifying a board size and the total number of generations to evolve the board over or by importing from file. The example below creates a 20 by 20 board that will evolve over 500 generations:

```
ConwayGameOfLife game(20, 500); 
```

The board can be populated either with randomly generated or user defined cells. The following will give each element on the board a 10% chance to generated a living cell:

```
game.populate(10);
```

A second argument can also be passed to seed the random number generator. 

To manually place cells, use the `set_cell` method. The following places a living cell (using the number 1) at the position (10, 10) on the board. 

```
game.set_cell(10, 10, 1);
```

A board can also be imported from file. The board size is passed as a second parameter:

```
game.import_from_file("myboard.txt", 10);
```

Finally, the `print_delay` method can be used to specify the rate at which a board is printed to console in seconds. The following prints a board every 0.25s:

```
game.print_delay_ = 0.25;
```

### TODO:
* Allow users to save boards to file
* Add python script to visualize board (images and videos)
* Restructure project files in repo
* Explore performance improvements (try 1D vector)

