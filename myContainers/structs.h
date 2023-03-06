#ifndef STRUCTS_H
#define STRUCTS_H
# include<iostream>
# include <vector>

struct TsmResult {
        std::vector<int> vertices;    // массив с искомым маршрутом (с порядком обхода вершин). Вместо int* можно использовать std::vector<int>
        double distance;  // длина этого маршрута
};

struct antData {
        TsmResult res;
        std::vector<int> checked;
        bool isElit;
};

#endif
