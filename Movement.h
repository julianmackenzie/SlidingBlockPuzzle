//  Author Information

//  File Information

#include <set>
#include <string>
#include <vector>
#include <queue>
#include "Grid.h"

using namespace std;

class Movement{

    private:
    set<string> configs;  // used to store simplified grid configs for avoiding redundant moves
    queue<Grid> bfsQueue;

    public:
    Movement(int r, int c, vector<string> initialGrid) {
        vector<string> ml;  // empty move list for initial grid
        Grid grid(r, c, ml);
        
        // TODO: Initialize each piece and add it to a starting grid

        // TODO: Add simplified initial layout to configs set

        // Add starting grid to the queue
        bfsQueue.push(grid);

    }

    ~Movement() {

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
        return false;
    }

};