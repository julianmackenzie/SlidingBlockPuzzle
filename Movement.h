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
    queue<Grid> bfsQueue;


    public:
    Movement(int r, int c) {
        this->rows = r;
        this->cols = c;
    }

    ~Movement() {

    }



    void importGrid(vector<string> initialConfig) {
        vector<string> ml;  // empty move list for initial grid
        Grid grid(this->rows, this->cols, ml);


        grid.importGrid(initialConfig);  // populate the grid with pieces from the data file


        grid.printGrid();  // initial print

        configs.emplace(grid.getSnapshot());  // Adds initial grid config to the set of all configs


        // Add starting grid to the queue
        bfsQueue.push(grid);
    }
    


    /*
     * function: processGrid()
     *
     * description: This function uses the initial grid state and performs what is essentially a breadth-
     * first search, revealing every possible move that can be made across the course of a game. It
     * adds these possible moves to a queue and iterates until it finds a state where the Z piece has
     * made it to the right side of the board. The BFS uses a queue, returning false if the queue ever
     * becomes empty and returning true once a solution is found. It also uses a set to store previous
     * configurations to ensure that no infinite loops occur.
     * 
     * 
     */
    bool processGrid() {
        bool solutionFound;
        while(!bfsQueue.empty()) {  // loop as long as there are unique moves to try
            Grid grid = bfsQueue.front();  // get next grid config

            if (grid.isSolved()) {  // if the Z piece has reached the goal
                solutionFound = true;
                break;
            }

            // TODO: Get all possible unique moves from grid, add them to bfsQueue, then check for solved state

            bfsQueue.pop();
        }

        return solutionFound;
    }

};