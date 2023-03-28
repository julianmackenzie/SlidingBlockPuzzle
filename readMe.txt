//  Author Information
Julian Mackenzie jbm5 662056584
Jiwon Jung jjung65 668675721

//  File Information
Piece.h contains all of the necessary data members to represent a piece on the
board. This is very simple, containing only getter and setter functions.

Grid.h is where the bulk of the functionality lays. It's got a 2D matrix
representing the game board and a map holding all of the fragments of each Piece
(as they can be multiple spaces wide and tall). It has many functions, some of
which are designed as helper functions to be used inside of the class but could
also be helpful in some circumstances as standalone functions usable on a
particular class object. Abstraction was used where possible to avoid repeated
code.

Movement.h is the class that facilitates the BFS and the facade of "moving"
pieces (described below) and contains several structures which, when modified
using data in unique Grid objects, aid in this. The set "configs" holds all
unique places that a game's Pieces can be in, in a simplified string format.
The queue bfsQueue is the primary data structure in running the BFS. It holds
vectors of strings in a format identical to the initial data file import, so
that Grids can be easily constructed without necessarily storing a full
structure inside of another. There is an additional queue, mlQueue, to hold the
corresponding move lists for these Grids. They share the same "index" as their
respective Grids, so the Grid data will always be processed with its matching
list of moves.

//  Explaination of why you designed your program in the manner that you did.
The primary strategy that we used in creating this program was, instead of
creating hundreds and thousands of Grids and storing them all together in the
queue, to convert individual Grids back into data files to remake them when
needed. This means that only one Grid at a time is active, making processing
relatively simple and quick on most data sets. The other facet of our strategy
was in how we found the valid moves that each Piece in a Grid could make. Rather
than worrying about truly moving the Pieces across the Grid, saving copies of
the Grid, moving them however many more times they needed to be, then resetting
their positions for the next Piece's moveset, we elected to essentially "fake"
the movement. As the exported data from each Grid was in the same format as
the imported .data file, we could simply change the value of the Origin Piece
(the Piece at the top left corner that the .data files use), convert the Grid
to data file format as if that Piece were truly moved, then restore the data
member to its initial value. That way, the Piece would be imported into its new
position when the next configuration is loaded from the bfsQueue. Genius!

Keeping things in separate classes helped. Piece.h was set it and forget it.
Grid.h was treated as a single instance of a game board with pieces on it, and
Movement.h was treated as the universe facilitating every possible outcome of
Grid.h.

//  Did you create any additional classes?
No.

//  What structures did you use to keep track of the various parts of the programs solution?
//   - Why was this particular structure selected
//   - How did you use this structure
//   - These structures could be Library structures or Code you created yourself


bfsQueue and mlQueue:
A queue just made sense, as we're running a BFS. Add new data to the end,
process from the beginning. That way we'd get the shortest path to the solution.

configs set: It was suggested in the writeup to store simplified strings for
easy compares, and after considering alternatives this was chosen as the best
option.

grid board 2d vector: This was the simplest way to throw together the game
board, and would be fine for runtime as there are no searches on it (thanks to
the map of pieces).

map of Pieces:
this was the most useful tool for solving some of the harder problems of the
project. How to make sure all the pieces can be moved without having to search
for them in the matrix, how to actually do the moves themselves, all of these
were made simple and quick by storing all of the Pieces in a map by ID.
The map's keys were the IDs of each piece (stored in ID order) and the values
were a vector containing each Piece with the Origin Piece (top left) at index 0.
Nice and easy!

We wrote about the real specifics of using these above, in the Explanation
section.