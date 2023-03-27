//    Author Information
// Jiwon Jung (Keith) did this go through?
// Julian Mackenzie yes!

//    Program information

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
  cout << "Using data from puzzle: " << argv[1] << endl;
  
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
    cout << line << endl;    // TODO: REMOVE
  }





  Movement mov(r, c);  // initialize the simulation



  // add pieces to grid and print grid
  mov.importData(initialConfig);

  mov.processGrid();


  
  //  find solution if one exists
  
  return 0;
}
