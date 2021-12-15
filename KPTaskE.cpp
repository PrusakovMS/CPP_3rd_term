#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Cell final{
public:
    char v; // Вертикаль, от 'A' до 'H'
    unsigned short int h; // Горизонталь, от '1' до '8'
    Cell(char v, unsigned short int h) : v(v), h(h) { } // Конструктор заданной клетки поля с параметрами
    Cell() : Cell('A', 1) { } // Конструктор клетки по умолчанию
};

class Piece {
public:
    Cell n;
    explicit Piece(Cell c) {
        n = c;
    }
    virtual bool available(Cell c){
        return false;
    };
};

class King:public Piece{
public:
    explicit King(Cell c) : Piece(c) { }
    bool available(Cell c) override {
        int x = c.v - n.v;
        int y = c.h - n.h;
        if(x == 0 && y == 0)
            return false;
        if(x >= -1 && x <= 1 && y >= -1 && y <= 1)
            return true;
        else
            return false;
    }
};

class Bishop:public Piece {
public:
    explicit Bishop(Cell c) : Piece(c) { }
    bool available(Cell c) override {
        int x = c.v - n.v;
        int y = c.h - n.h;
        if(x == 0 && y == 0)
            return false;
        if(x == y || x == -y)
            return true;
        else
            return false;
    }
};
class Rook : public Piece {
public:
    explicit Rook(Cell c) : Piece(c) { }
    bool available(Cell c) override{
        if(c.h == n.h && c.v == n.v)
            return false;
        if(c.h == n.h || c.v == n.v)
            return true;
        else
            return false;
    }
};
class Queen:public Piece {
public:
    explicit Queen(Cell c) : Piece(c) { }
    bool available(Cell c) override {
        int x = c.v - n.v;
        int y = c.h - n.h;
        if(c.h == n.h && c.v == n.v)
            return false;
        if(x == 0 && y == 0)
            return false;
        if(c.h == n.h || c.v == n.v || x == y || x == -y)
            return true;
        else
            return false;
    }
};


	vector <bool> are_available(Cell c, std::vector<Piece*> const &pieces) {
    vector<bool> answ;
    for (auto p : pieces)
        answ.push_back(p->available(c));
    return answ;
}


int main() {
    vector<Piece *> pieces;
    pieces.push_back(new King(Cell('A', 1)));
    pieces.push_back(new Queen(Cell('A', 1)));
    pieces.push_back(new Rook(Cell('A', 1)));
    pieces.push_back(new Bishop(Cell('A', 1)));

    for(auto y : are_available(Cell('A',1),pieces))
        cout << y << ' ';
    cout << endl;

    for (auto p: pieces)
        delete p;

    return 0;
}