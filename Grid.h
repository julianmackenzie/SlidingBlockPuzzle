//  Author Information

//  File Information

#include <vector>
#include <string>
#include "Piece.h"

using namespace std;



class Grid {
    private:
    int rows, cols;
    vector<vector<Piece>> board;

    // Data Member "moves": 
    // used to store moves up to the current board in format "xyz"
    // x: letter or number identifier for piece
    // y: direction moved
    // z: number of spaces moved in that direction
    vector<string> moves;

    public:
        Grid(int r, int c, vector<string> moveList) {
            this->rows = r;
            this->cols = c;
            this->moves = moveList;

        }
        ~Grid() {

        }


    /*
     * function: printGrid()
     *
     * description: This function will print a grid in its current state.
     */
    void printGrid() {
    // Print top border
    for (int i = 0; i < cols + 2; i++) {
        cout << "*";
    }
    cout << endl;

    // Print grid contents
    for (int i = 0; i < rows; i++) {
        cout << "*";
        for (int j = 0; j < cols; j++) {
            if (board[i][j].isEmpty()) {
                cout << ".";
            } else {
                cout << board[i][j].getIdentifier();
            }
        }
        cout << "*" << endl;
    }

    // Print bottom border
    for (int i = 0; i < cols + 2; i++) {
        cout << "*";
    }
    cout << endl;
}


// And I think we need to put the following code at main

/*
// read in input file and set up initial puzzle configuration
while (std::getline(the_file, line)) {
    std::vector<Piece> row;
    for (int j = 0; j < c; j++) {
        if (line[j] == '.') {
            row.push_back(Piece());
        } else {
            row.push_back(Piece(line[j]));
        }
    }
    board.push_back(row);
}

// Print initial grid state
cout << "Initial Grid:" << endl;
printGrid();

*/


};