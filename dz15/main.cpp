#include <iostream>
#include "TSP.h"
#include "Testing.h"

int main() {
    int a, b, size; // левая и правая границы
    std::cout << "Левая граница: ";
    std::cin >> a;
    std::cout << "Правая граница: ";
    std::cin >> b;
    std::cout << "Размер выборки: ";
    std::cin >> size;
    std::vector<int> points;
    for (int i = a; i <= b; i++) {
        points.push_back(i);
    }
    Testing::test(points, size);
    return 0;
}