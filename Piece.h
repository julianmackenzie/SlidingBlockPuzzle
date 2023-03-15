//  Author Information

//  File Information

class Piece{
    private:

    int row, col, width, height;
    char movement;

    public:

    Piece(int r, int c, int w, int h, char mm) {
        this->row = r;
        this->col = c;
        this->width = w;
        this->height = h;
        this->movement = mm;
    }
    ~Piece() {

    }

    int getRow() {
        return this->row;
    }
    int getCol() {
        return this->col;
    }
    int getWidth() {
        return this->width;
    }
    int getHeight() {
        return this->height;
    }




};