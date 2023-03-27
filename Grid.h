//  Author Information

//  File Information

#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include "Piece.h"

using namespace std;



class Grid {
    private:
    int rows, cols;
    vector<vector<Piece*>> board;

    map<char, vector<Piece*>> pieces;  // will hold all Pieces for each ID for easy access

    int population;



    string idLibrary = "Z123456789ABCDEFGHIJKLMNOPQRSTUVWXY";


    // Data Member "moves": 
    // used to store moves up to the current board in format "xyz*"...
    // x: letter or number identifier for piece
    // y: direction moved
    // z: number of spaces moved in that direction
    // ...repeated any number of times
    string moves;

    public:
        Grid(int r, int c) {
            this->rows = r;
            this->cols = c;
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
     */
    void importGrid(vector<string> initialConfig, string moveList, bool firstTime) {
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
                if (firstTime == true) {
                    cout << "Warning: Piece with starting position of " << row 
                    << "," << col << "has invalid movement" << endl;
                }

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

                if (firstTime == true) {
                    cout << "Warning: Piece with starting position of " << row+1 
                    << "," << col+1 << " falls outside of grid" << endl;
                }
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

                        if (firstTime == true) {
                            cout << "Warning: Piece with starting position of " <<
                            row+1 << "," << col+1 << " overlaps with other piece"
                            << endl;
                        }
                        errorFound = true;
                        break;  // don't need to keep checking
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
                    this->pieces[identifier].push_back(newPiece);  // add Piece to map of Pieces

                    this->moves = moveList;  // import Move List
                    
                    this->board[row+i][col+j] = newPiece;  // add piece to board
                }
            }
            
        }
    }





    /*
     * function: exportGrid()
     * 
     * description: Imitates the creation of a .data file using a preexisting grid
     */
    vector<string> exportGrid() {

        vector<string> config;
        for (int i=0; i<this->population; i++) {

            // grab first piece of a block (origin piece). this is done in the order pieces are created in
            Piece* originPiece = this->pieces[idLibrary[i]][0];  

            string acc = "";
            acc += to_string(originPiece->getRow()+1);  // Account for data files being 1-indexed
            acc += " ";
            acc += to_string(originPiece->getCol()+1);  // Account for data files being 1-indexed
            acc += " ";
            acc += to_string(originPiece->getWidth());
            acc += " ";
            acc += to_string(originPiece->getHeight());
            acc += " ";
            acc += originPiece->getMovement();

            config.push_back(acc);
        }

        return config;
    }


    /*
     * function: exportMovelist()
     *
     * description: simple getter that fetches the grid's current movelist.
     * used alongside exportGrid() to get all needed data for BFS
     */
    string exportMovelist() {
        return this->moves;
    }




    /*
     * function: tryMove
     *
     * description: This is a helper function for findAllMoves().
     * Attempts all possibe moves on a single piece in a single direction.
     * 
     */
    void tryMove(vector<vector<string>> &pieceConfigs, vector<string> &mlData, int id, char dir) {

        int dist = 1;
        bool canMove = true;  // set to true to start

        while (canMove == true) {
            for (Piece* p : this->pieces[this->idLibrary[id]]) {  // check each part of the piece for collisions
                
                // find prospective new coordinate for piece
                int newPlace;
                if (dir == 'u') newPlace = p->getRow()-dist;
                if (dir == 'd') newPlace = p->getRow()+dist;
                if (dir == 'l') newPlace = p->getCol()-dist;
                if (dir == 'r') newPlace = p->getCol()+dist;

                
                // bounds check (don't attempt out of bounds moves)
                if (dir == 'u' || dir == 'd') {
                    if (newPlace < 0 || newPlace >= this->rows) {
                        canMove = false;
                        break;
                    }
                }
                if (dir == 'l' || dir == 'r') {
                    if (newPlace < 0 || newPlace >= this->cols) {
                        canMove = false;
                        break;
                    }
                }

                
                // collision check
                if (dir == 'u' || dir == 'd') {
                    // if new spot is filled by a different piece
                    if (this->board[newPlace][p->getCol()] != nullptr && 
                                                this->board[newPlace][p->getCol()]->getID() != p->getID()) {
                        canMove = false;  // changes to false if any part of the piece collides
                        break;
                    }
                }
                if (dir == 'l' || dir == 'r') {
                    // if new spot is filled by a different piece
                    if (this->board[p->getRow()][newPlace] != nullptr && 
                                                this->board[p->getRow()][newPlace]->getID() != p->getID()) {
                        canMove = false;  // changes to false if any part of the piece collides
                        break;
                    }
                }

            }




            if (canMove == true) {  // if entire piece is able to move [dist] in given direction
                int oldPlace;
                
                
                if (dir == 'u' || dir == 'd') {
                    oldPlace = this->pieces[this->idLibrary[id]][0]->getRow();  // store old location
                    if (dir == 'u') this->pieces[this->idLibrary[id]][0]->setRow(oldPlace-dist);  // fake move to new location
                    if (dir == 'd') this->pieces[this->idLibrary[id]][0]->setRow(oldPlace+dist);  // fake move to new location
                }
                if (dir == 'l' || dir == 'r') {
                    oldPlace = this->pieces[this->idLibrary[id]][0]->getCol();  // store old location
                    if (dir == 'l') this->pieces[this->idLibrary[id]][0]->setCol(oldPlace-dist);  // fake move to new location
                    if (dir == 'r') this->pieces[this->idLibrary[id]][0]->setCol(oldPlace+dist);  // fake move to new location
                }

                pieceConfigs.push_back(this->exportGrid());  // add entire setup to our BFS queue return
                
                // assemble string to represent move
                string move = this->exportMovelist();
                move += this->pieces[this->idLibrary[id]][0]->getID();  // id
                if (dir == 'u') move += "u";  // direction
                if (dir == 'd') move += "d";
                if (dir == 'l') move += "l";
                if (dir == 'r') move += "r";
                
                move += to_string(dist);  // distance
                
                mlData.push_back(move);  // add move to our movelist queue return
                
                // reset piece to starting spot
                if (dir == 'u' || dir == 'd') this->pieces[this->idLibrary[id]][0]->setRow(oldPlace);  
                if (dir == 'l' || dir == 'r') this->pieces[this->idLibrary[id]][0]->setCol(oldPlace);  
                
            }

            dist++;
        }
    }



    // TODO: for each possible move, use exportGrid to get pieceConfig, exportMovelist to get mlData,
    // and simplify to get simple string for simplifiedConfig

    void findAllMoves(vector<vector<string>> &pieceConfigs, vector<string> &mlData) {
        for (int i=0; i<this->population; i++) {
            char movement = this->pieces[this->idLibrary[i]][0]->getMovement();
            if (movement == 'n') continue;
            else {
                bool canMove;
                if (movement == 'b' || movement == 'v') {
                    tryMove(pieceConfigs, mlData, i, 'u');
                    tryMove(pieceConfigs, mlData, i, 'd');
                }
                if (movement == 'b' || movement == 'h') {
                    tryMove(pieceConfigs, mlData, i, 'l');
                    tryMove(pieceConfigs, mlData, i, 'r');
                }
            }
        }

        return;
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
     * function: simplify()
     * 
     * description: This function returns piece data of the grid in simple string format. This will be used
     * to easily compare grid states so that no two configurations are ever visited twice.
     */
    string simplify() {
        string simplified = "";
        // Append the current state of the board
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                if (this->board[i][j] == nullptr) {
                    simplified += " ";  // no piece here
                } else {
                    simplified += this->board[i][j]->getID();  // piece here
                }
            }
        }

        return simplified;
    }



    /*
     * function: isSolved()
     * 
     * description: return a boolean value, true if the grid has a Z piece at the right side of the board
     * and false if not.
     */
    bool isSolved() {
        bool atGoal = false;
        for (Piece* p : this->pieces['Z']) {
            if (p->getCol() == this->cols-1) atGoal = true;
        }

        return atGoal;
    }





};





