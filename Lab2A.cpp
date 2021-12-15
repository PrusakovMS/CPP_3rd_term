#include <iostream>
#include <ostream>

using namespace std;


template <typename T>
class Grid {
private:
    T * memory;
    size_t x_size, y_size;
public:

    Grid(): memory(nullptr), x_size(0), y_size(0) { }

    Grid(size_t x_size, size_t y_size){
        this->x_size = x_size;
        this->y_size = y_size;
        this->memory = new T[x_size * y_size];
        cout << "Added " << memory << endl;
    }

    ~Grid() {
        if (memory) {
            delete[] memory;
            cout << "Deleted " << memory << endl;
        }
    }

    Grid<T>(Grid<T> const &src): Grid<T>(src.get_xsize(), src.get_ysize()) {
        for (size_t cnt = 0; cnt != src.get_xsize() * src.get_ysize(); ++cnt) {
            memory[cnt] = src.memory[cnt];
        }
    }

    Grid<T>& operator=(Grid<T> const &src) {
        Grid<T> tmp(src);
        swap(this->memory, tmp.memory);
        swap(this->x_size, tmp.x_size);
        swap(this->y_size, tmp.y_size);
        return *this;
    }

    Grid<T>(Grid<T> &&src): Grid() {
        swap(this->memory, src.memory);
        swap(this->x_size, src.x_size);
        swap(this->y_size, src.y_size);
    }

    Grid<T>& operator=(Grid<T> &&src) {
        Grid<T> tmp(std::move(src));
        swap(this->memory, tmp.memory);
        swap(this->x_size, tmp.x_size);
        swap(this->y_size, tmp.y_size);
    }

    Grid& operator=(T elem) {
        for (size_t cnt = 0; cnt != x_size * y_size; ++cnt) {
            memory[cnt] = elem;
        }
        return *this;
    }

    T& operator()(size_t x_idx, size_t y_idx) {
        return memory[x_idx + x_size*y_idx];
    }

    T operator()(size_t x_idx, size_t y_idx) const {
        return memory[x_idx + x_size*y_idx];
    }

    size_t get_xsize() const {
        return x_size;
    }

    size_t get_ysize() const {
        return y_size;
    }

    template <typename U>
    friend ostream& operator<<(ostream&, Grid<U> const&);
    template <typename U>
    friend istream& operator>>(istream&, Grid<U> &);
};

template <typename T>
ostream& operator<<(ostream& os, Grid<T> const& gr) {
    for (size_t y_idx = 0; y_idx < gr.get_ysize(); ++y_idx) {
        for (size_t x_idx = 0; x_idx < gr.get_xsize(); x_idx++) {
            os << gr(x_idx, y_idx) << " ";
        }
        os << endl;
    }
    return os;
}

template <typename T>
istream& operator>>(istream& is, Grid<T> & gr) {
    for (size_t y_idx = 0; y_idx < gr.get_ysize(); ++y_idx) {
        for (size_t x_idx = 0; x_idx < gr.get_xsize(); x_idx++) {
            is >> gr(x_idx, y_idx);
        }
    }
    return is;
}

int main() {
    Grid<int> gr1(2, 2);
    gr1 = 0;
    gr1(1, 1) = 1;
    cout << gr1;

    Grid<int> gr2(3, 3);
    gr2 = 0;
    cout << gr2;
    gr2 = gr1;
    cout << gr2;

    Grid<int> gr3(gr1);
    cout << gr3;

    Grid<int> gr4(2, 2);
    cin >> gr4;
    cout << gr4;
    return 0;
}
