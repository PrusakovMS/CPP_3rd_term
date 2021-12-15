#include <iostream>
#include <ostream>

using namespace std;

template <typename T>
union MemoryCell;

template <typename T>
class Grid {
private:
    MemoryCell<T> * memory;
    bool * subgrids;
    size_t x_size, y_size;
public:

    Grid(): memory(nullptr), x_size(0), y_size(0) { }

    Grid(size_t x_size, size_t y_size){
        this->x_size = x_size;
        this->y_size = y_size;
        this->memory = new MemoryCell<T>[x_size * y_size];
        this->subgrids = new bool[x_size * y_size];
        for (size_t cnt = 0; cnt != this->x_size * this->y_size; ++cnt) {
            subgrids[cnt] = false;
        }
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
        swap(this->subgrids, tmp.subgrids);
        return *this;
    }

    Grid<T>(Grid<T> &&src): Grid() {
        swap(this->memory, src.memory);
        swap(this->x_size, src.x_size);
        swap(this->y_size, src.y_size);
        swap(this->subgrids, src.subgrids);
    }

    Grid<T>& operator=(Grid<T> &&src) {
        Grid<T> tmp(std::move(src));
        swap(this->memory, tmp.memory);
        swap(this->x_size, tmp.x_size);
        swap(this->y_size, tmp.y_size);
        swap(this->subgrids, tmp.subgrids);
    }

    Grid& operator=(T elem) {
        for (size_t cnt = 0; cnt != x_size * y_size; ++cnt) {
            memory[cnt].data = elem;
            subgrids[cnt] = false;
        }
        return *this;
    }

    T& operator()(size_t x_idx, size_t y_idx) {
        if (this->is_subgrid(x_idx, y_idx)) {
            throw "Binding lvalue reference to rvalue";
        }
        else {
            return memory[x_idx + x_size*y_idx].data;
        }
    }

    T operator()(size_t x_idx, size_t y_idx) const {
        if (this->is_subgrid(x_idx, y_idx)) {
            return memory[x_idx + x_size*y_idx].subgrid->average();
        }
        else {
            return memory[x_idx + x_size*y_idx].data;
        }
    }

    size_t get_xsize() const {
        return x_size;
    }

    size_t get_ysize() const {
        return y_size;
    }

    T average() const {
        T avg = 0;
        for (size_t cnt = 0; cnt != x_size * y_size; ++cnt) {
            if (subgrids[cnt]) {
                avg += memory[cnt].subgrid->average();
            }
            else {
                avg += memory[cnt].data;
            }
        }
        return avg/(x_size * y_size);
    }

    Grid& make_subgrid(size_t x_idx, size_t y_idx, size_t x_sub_size, size_t y_sub_size) {
        if (this->is_subgrid(x_idx, y_idx)) {
            T avg = memory[x_idx + x_size*y_idx].subgrid->average();
            memory[x_idx + x_size*y_idx].subgrid = new Grid(x_sub_size, y_sub_size);
            *memory[x_idx + x_size*y_idx].subgrid = avg;
        }
        else {
            T avg = memory[x_idx + x_size*y_idx].data;
            memory[x_idx + x_size*y_idx].subgrid = new Grid(x_sub_size, y_sub_size);
            *memory[x_idx + x_size*y_idx].subgrid = avg;
            subgrids[x_idx + x_size*y_idx] = true;
        }
        return *memory[x_idx + x_size*y_idx].subgrid;
    }


    T& collapse_subgrid(size_t x_idx, size_t y_idx) {
        if (this->is_subgrid(x_idx, y_idx)) {
            memory[x_idx + x_size*y_idx].data = memory[x_idx + x_size*y_idx].subgrid->average();
            subgrids[x_idx + x_size*y_idx] = false;
        }
        return memory[x_idx + x_size*y_idx].data;
    }

    Grid& get_subgrid(size_t x_idx, size_t y_idx) {
        return *memory[x_idx + x_size*y_idx].subgrid;
    }

    Grid const& get_subgrid(size_t x_idx, size_t y_idx) const {
        return memory[x_idx + x_size*y_idx].subgrid;
    }

    bool is_subgrid(size_t x_idx, size_t y_idx) const {
        return this->subgrids[x_idx + x_size*y_idx];
    }

    template <typename U>
    friend ostream& operator<<(ostream&, Grid<U> const&);
    template <typename U>
    friend istream& operator>>(istream&, Grid<U> &);
};

template <typename T>
union MemoryCell
{
    T data;
    Grid<T> * subgrid;
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
    cout << gr1 << endl;
    gr1(1, 1) = 2;
    gr1.make_subgrid(1, 1, 2, 2);
    cout << gr1 << endl;
    cout << "(1,1) is subgrid: " << gr1.is_subgrid(1, 1) << endl;
    cout << gr1.get_subgrid(1, 1) << endl;
    gr1.get_subgrid(1, 1) = 3;
    cout << gr1 << endl;
    cout << "(1,1) is subgrid: " << gr1.is_subgrid(1, 1) << endl;
    cout << gr1.get_subgrid(1, 1) << endl;
    gr1.collapse_subgrid(1, 1);
    cout << gr1 << endl;
    cout << "(1,1) is subgrid: " << gr1.is_subgrid(1, 1) << endl;
    return 0;
}
