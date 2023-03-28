//  Author Information
//  Julian Mackenzie jbm5 662056584
//  Jiwon Jung jjung65 668675721

//    Program information
/*
This program is a simulation of a Sliding Block puzzle game. In Grid.h, a board
with rectangular Pieces is created, with each Piece being allowed to move a 
specified set of directions across the board. The target is to get the first
placed piece, labeled "Z", to the right edge of the game board. This marks the
puzzle as solved.

What makes this program interesting is that it does not have the user play the
game. Instead, using a Breadth First Search, the program will solve the puzzle
for the user, outputting the list of moves that it took to get to the answer.
This will always be the shortest amount of moves that could be taken. It will
also recognize when a problem is completely impossible to solve.

The functionality is split across three header files:
Movement.h - where the BFS happens and many, many Grid instances are processed
Grid.h - where any particular moment of the game is represented as a board filled
with Pieces
Piece.h - where the bare data for the location and size of each Piece is held.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Movement.h"

using namespace std;

int main(int argc, char** argv){
  if ( argc != 2 ) { // argc should be 2 for correct execution
    // We print argv[0] assuming it is the program name
    cout<<"usage: "<< argv[0] <<" <filename>\n";
    exit(0);
  }
 
  // We assume argv[1] is a filename to open
  ifstream the_file ( argv[1] );
  // Always check to see if file opening succeeded
  if ( !the_file.is_open() ) {
    cout<<"Could not open file: " << argv[1] << "\n";
    exit(0);
  }

  cout << "Welcome to Sliding Block Puzzle\n";
  cout << "Using data from puzzle: " << argv[1] << endl << endl;
  
  bool done = false;
  string line;
  string input;

  vector<string> initialConfig;

  getline(the_file, line);
  char r = line[0] - 48;  // grab row count and "convert" to int
  char c = line[3] - 48;  // grab col count and "convert" to int



  // Grid size error checking
  if (r <= 0) {
    cout << "Error: Number of rows must be greater than zero" << endl;
    return -1;
  }
    if (c <= 0) {
    cout << "Error: Number of columns must be greater than zero" << endl;
    return -1;
  }



  // read in input file and set up initial puzzle configuration
  while (std::getline(the_file, line)) {
    std::istringstream iss(line);
    initialConfig.push_back(line);  // add each piece's initial state into vector
  }





  Movement mov(r, c);  // initialize the simulation



  // add pieces to grid and print grid
  mov.importData(initialConfig);

  mov.processGrid();


  
  //  find solution if one exists
  
  return 0;
}
