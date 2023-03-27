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
            // TODO: Free Pieces from memory when done with Grid
        }


    

    
    /*
     * function: importGrid()
     *
     * description: This function is used to initialize a Grid from a .data
     * file. It will populate the Grid with Piece objects. Additionally, this
     * will screen each Piece as it is imported to ensure that only valid Piece
     * placements will be added to the Grid.
     * 
     */
    void importGrid(vector<string> initialConfig) {
        // Go through vector of lines from the data file to import at Pieces
        for (string s : initialConfig) {

            // Data members for Piece
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



            bool errorFound = false;  // will be used to correctly skip errant pieces

            // Movement error check
            if (movement != 'v' && movement != 'h' && movement != 'b' 
                                                && movement != 'n')
            {
                cout << "Warning: Piece with starting position of " << row 
                << "," << col << "has invalid movement" << endl;
                errorFound = true;
            }

            if (errorFound) {
                continue;
            }


            // Get unique identifier
            char identifier = idLibrary[this->population];
            this->population++;


            // Bounds error check (full piece)
            if (row >= this->rows || col >= this->cols || 
                row+(height-1) >= this->rows || col+(width-1) >= this->cols) {

                cout << "Warning: Piece with starting position of " << row+1 
                << "," << col+1 << " falls outside of grid" << endl;
                errorFound = true;
            }

            if (errorFound) {
                population--;
                continue;
            }


            // Collision error check (full piece)
            for (int i=0; i<height; i++) {
                for (int j=0; j<width; j++) {
                    if (this->board[row+i][col+j] != nullptr) {

                        cout << "Warning: Piece with starting position of " <<
                        row+1 << "," << col+1 << " overlaps with other piece"
                        << endl;
                        errorFound = true;
                        break;  // don't need to keep checking/>1 error message
                    }
                }
            }

            if (errorFound) {
                population--;
                continue;
            }



            //
            // Code below this line will execute only if the whole piece will be valid
            //


            // add all parts of the Piece to the board
            for (int i=0; i<height; i++) {
                for (int j=0; j<width; j++) {
                    Piece *newPiece = new Piece(row+i, col+j, width, height, 
                                                    movement, identifier);
                    this->board[row+i][col+j] = newPiece;  // add piece to board
                }
            }
            
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




    /*
     *
     * function: getSnapshot()
     * 
     * description: This function returns critical data of the grid in string format. This will be used to
     * easily compare grid states so that no two configurations are ever visited twice.
     * 
     */
    string getSnapshot() {
        string snapshot = "";

        // Append the number of rows and columns
        snapshot += to_string(this->rows) + ";" + to_string(this->cols) + ";";

        // Append the population count
        snapshot += to_string(this->population) + ";";

        // Append the current moves
        for (string move : this->moves) {
            snapshot += move + ",";
        }
        // Remove the trailing comma
        snapshot.pop_back();
        snapshot += ";";

        // Append the current state of the board
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                if (this->board[i][j] == nullptr) {
                    snapshot += " ";
                } else {
                    snapshot += this->board[i][j]->getID();
                }
            }
            snapshot += ";";
        }

        // Remove the trailing semicolon
        snapshot.pop_back();

        return snapshot;
    }



    /*
     *
     * function: isSolved()
     * 
     * description: return a boolean value, true if the grid has a Z piece at the right side of the board
     * and false if not.
     * 
     */
    bool isSolved() {
        // TODO: Implement

        return false;
    }





};





