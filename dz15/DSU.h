//
// Created by Nikita on 19.12.2019.
//

#pragma once

#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>

class DSU {
public:
    explicit DSU(size_t size);

    int find(int element);
    void merge(int left, int right);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

