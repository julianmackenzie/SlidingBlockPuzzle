//  Author Information
//  Julian Mackenzie jbm5 662056584
//  Jiwon Jung jjung65 668675721

//  File Information
/*
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
*/

#include <set>
#include <string>
#include <vector>
#include <queue>
#include "Grid.h"

using namespace std;

class Movement {

    private:
    int rows;
    int cols;

    set<string> configs;  // used to store simplified grid configs for avoiding redundant moves
    queue<vector<string>> bfsQueue;  // grids used in solution BFS in data file format
    queue<string> mlQueue;  // queue of moveLists whose indices correspond to bfsQueue data


    public:
    Movement(int r, int c) {
        this->rows = r;
        this->cols = c;
    }

    ~Movement() {

    }



    void importData(vector<string> initialConfig) {
        Grid grid(this->rows, this->cols);


        string ml = "";  // empty move list for initial grid
        grid.importGrid(initialConfig, ml, true);  // populate the grid with pieces from the data file


        grid.printGrid();  // initial print

        // Add starting grid to the queue
        bfsQueue.push(initialConfig);
        mlQueue.push(ml);
    }
    


    /*
     * function: processGrid()
     *
     * description: This function uses the initial grid state and performs what is essentially a breadth-
     * first search, revealing every possible move that can be made across the course of a game. It
     * adds these possible moves to a queue and iterates until it finds a state where the Z piece has
     * made it to the right side of the board. The BFS uses a queue, returning false if the queue ever
     * becomes empty and returning true once a solution is found. It also uses a set to store previous
     * configurations to ensure that no infinite loops occur, and a queue of movelists that correspond
     * to the BFS queue's piece configurations (parallel queues).
     * 
     * 
     */
    bool processGrid() {
        while(!bfsQueue.empty()) {  // loop as long as there are unique moves to try
            
            Grid grid(this->rows, this->cols);  // make a grid to hold the current data

            vector<string> pieceData = bfsQueue.front();  // get next grid config
            string ml = mlQueue.front();  // get next grid's movelist

            grid.importGrid(pieceData, ml, false);  // add data for this iteration's grid


            string currentConfig = grid.simplify();  // get simplified grid config

            if (this->configs.count(currentConfig)) {  // if this is not a unique grid, don't process it
                bfsQueue.pop();
                mlQueue.pop();
                continue;
            }

            this->configs.emplace(grid.simplify());  // if this is a unique grid, add its simplified config to map


            if (grid.isSolved()) {  // if the Z piece has reached the goal
                break;
            }


            
            vector<vector<string>> validMoves;  // compiled list of valid moves
            vector<string> validMovelists;  // compiled list of corresponding movelists
            grid.findAllMoves(validMoves, validMovelists);


            // Adding found moves and respective movelists to back of queues
            for (int i=0; i<validMoves.size(); i++) {
                bfsQueue.push(validMoves[i]);
                mlQueue.push(validMovelists[i]);
            }





            bfsQueue.pop();  // Done with this grid, remove from queue of grids
            mlQueue.pop();  // move to next corresponding movelist, too
        }



        // Solution found
        if (bfsQueue.size() != 0) {
            
            Grid grid(this->rows, this->cols);
            vector<string> pieceData = bfsQueue.front(); // get solved grid's piece data
            string ml = mlQueue.front();  // get solved grid's movelist
            grid.importGrid(pieceData, ml, false);  // load solved grid

            // Print movelist of solution and number of moves (movelist size/3)
            cout << endl << "This puzzle is solvable in " << ml.size()/3 << " steps" << endl << endl;

            grid.printGrid();
            cout << endl;
            
            int i=0;
            while (i<ml.size()) {
                cout << i/3 + 1 << ". Piece " << ml[i] << " moves " << ml[i+2] << " spaces(s) ";
                if (ml[i+1] == 'u') cout << "up" << endl;
                if (ml[i+1] == 'd') cout << "down" << endl;
                if (ml[i+1] == 'l') cout << "left" << endl;
                if (ml[i+1] == 'r') cout << "right" << endl;
                i += 3;
            }

            return true;
            
        }


        // No solution found
        cout << "This puzzle has no solution" << endl;
        return false;


    }

};