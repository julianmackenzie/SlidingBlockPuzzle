//  Author Information

//  File Information

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
        grid.importGrid(initialConfig, ml);  // populate the grid with pieces from the data file


        grid.printGrid();  // initial print

        configs.emplace(grid.simplify());  // Adds initial grid config to the set of all configs


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
        bool solutionFound;
        while(!bfsQueue.empty()) {  // loop as long as there are unique moves to try
            
            Grid grid(this->rows, this->cols);  // make a grid to hold the current data

            vector<string> pieceData = bfsQueue.front();  // get next grid config
            string ml = mlQueue.front();  // get next grid's movelist

            grid.importGrid(pieceData, ml);  // add data for this iteration's grid

            if (grid.isSolved()) {  // if the Z piece has reached the goal
                solutionFound = true;  // we found the shortest solution!
                break;
            }


            vector<vector<string>> validMoves;  // compiled list of valid moves
            vector<string> validMovelists;  // compiled list of corresponding movelists
            vector<string> validGridConfigs;  // stores simplified grids to sort out non-unique moves
            grid.findAllMoves(validMoves, validMovelists, validGridConfigs);


            // Adding to back of queues
            for (int i=0; i<validMoves.size(); i++) {
                if (!this->configs.count(validGridConfigs[i])) {  // if move leads to a unique grid
                    bfsQueue.push(validMoves[i]);
                    mlQueue.push(validMovelists[i]);
                }
            }





            bfsQueue.pop();  // Done with this grid, remove from queue of grids
            mlQueue.pop();  // move to next corresponding movelist, too
        }

        if (solutionFound) {
            // TODO: Print movelist of solution and number of moves (movelist size/3)
        }
        else {
            cout << "This puzzle has no solution" << endl;
        }


        return solutionFound;
    }

};