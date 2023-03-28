//  Author Information
//  Julian Mackenzie jbm5 662056584
//  Jiwon Jung jjung65 668675721

//  File Information
/*
Piece.h contains all of the necessary data members to represent a piece on the
board. This is very simple, containing only getter and setter functions.
*/

#include <string>


using namespace std;

class Piece {
    private:

    int row, col, width, height;
    char movement;
    char id;

    public:

    Piece(int r, int c, int w, int h, char mm, char identifier) {
        this->row = r;
        this->col = c;
        this->width = w;
        this->height = h;
        this->movement = mm;
        this->id = identifier;
    }
    ~Piece() {

    }

    int getRow() {
        return this->row;
    }
    void setRow(int r) {
        this->row = r;
    }
    int getCol() {
        return this->col;
    }
    void setCol(int c) {
        this->col = c;
    }
    int getWidth() {
        return this->width;
    }
    int getHeight() {
        return this->height;
    }
    char getMovement() {
        return this->movement;
    }
    char getID() {
        return this->id;
    }




};