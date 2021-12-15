#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Nabl {
    int64_t d;
    int64_t m;
    int64_t y;
    int64_t n;
};

struct NablCmp {
    bool operator() (const Nabl& a, const Nabl& b) const {
        if (a.y != b.y) {
            return a.y <= b.y;
        }
        if (a.m != b.m) {
            return a.m <= b.m;
        }
        return a.d <= b.d;
    }
};

int main() {
    size_t N;
    cin >> N;
    set<Nabl, NablCmp> data;
    for (size_t i = 0; i < N; i++) {
        Nabl nabl;
        scanf("%ld.%ld.%ld %ld", &nabl.d, &nabl.m, &nabl.y, &nabl.n);
        if (data.find(nabl) == data.end()) {
            data.insert(nabl);
        } else {
            data.erase(nabl);
            data.insert(nabl);
        }
    }

    size_t M;
    cin >> M;
    NablCmp cmp;
    for (size_t i = 0; i < M; i++) {
        Nabl nabl;
        scanf("%ld.%ld.%ld", &nabl.d, &nabl.m, &nabl.y);

        auto search = data.begin();
        int64_t max = 0;
        while (cmp(*search, nabl) && (search != data.end())) {
            if (search->n > max) {
                max = search->n;
            }
            search++;
        }
        cout << max << '\n';
    }
    return 0;
}