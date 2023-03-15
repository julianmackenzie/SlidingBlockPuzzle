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
        // TODO: implement grid print
    }


};