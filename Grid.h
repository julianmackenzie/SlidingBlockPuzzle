//  Author Information

//  File Information

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Piece.h"

using namespace std;



class Grid {
    private:
    int rows, cols;
    vector<vector<Piece*>> board;

    int population;



    string idLibrary = "Z123456789ABCDEFGHIJKLMNOPQRSTUVWXY";


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
            this->population = 0;

            vector<vector<Piece*>> newBoard(r, vector<Piece*>(c, nullptr));

            this->board = newBoard;
            

        }
        ~Grid() {

        }


    

    

    void importGrid(vector<string> initialConfig) {
        // Go through vector of lines from the data file
        for (string s : initialConfig) {

            
            int row;
            int col;
            int width;
            int height;
            char movement;

            // Use stringstream to add data pieces from formatted string
            stringstream data(s);
            data >> row >> col >> width >> height >> movement;
            
            // account for the fact that the game is 1-indexed
            row--;  
            col--;


            // Movement error check
            if (movement != 'v' && movement != 'h' && movement != 'b' 
                                                && movement != 'n')
            {
                cout << "Warning: Piece with starting position of " << row 
                << "," << col << "has invalid movement" << endl;
                continue;
            }

            // Get unique identifier
            char identifier = idLibrary[this->population];
            this->population++;


            // Bounds error check (starting location)
            if (row >= this->rows || col >= this->cols) {
                cout << "Warning: Piece with starting position of " << row 
                << "," << col << "falls outside of grid" << endl;
                population--;
                continue;
            }


            // Collision eror check (starting location)
            if (this->board[row][col] != nullptr) {
                cout << "Warning: Piece with starting position of " << row 
                << "," << col << "overlaps with other piece" << endl;
                population--;
                continue;
            }


            // add piece of block (starting location)
            Piece newPiece(row, col, width, height, movement, identifier);
            this->board[row][col] = &newPiece;


            // ERROR: Uncomment this line to make it almost work? All pieces in printed grid are identical though, the final piece to be added...
            // cout << "ID: " << this->board[row][col]->getID() << endl;

            // TODO: Add more pieces of a block based on width and height and successfully undo all if an error occurs

        }

    }













    /*
     * function: printGrid()
     *
     * description: This function will print a grid in its current state.
     */
    void printGrid() {
        // Print top border
        for (int i = 0; i < this->cols + 2; i++) {
            cout << "*";
        }
        cout << endl;

        // Print grid contents
        for (int i = 0; i < this->rows; i++) {
            cout << "*";
            for (int j = 0; j < cols; j++) {
                if (this->board[i][j] == nullptr) {
                    cout << ".";
                } else {
                    cout << this->board[i][j]->getID();
                }
            }
            cout << "*" << endl;
        }

        // Print bottom border
        for (int i = 0; i < this->cols + 2; i++) {
            cout << "*";
        }
        cout << endl;
    }




};