//  Author Information

//  File Information

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