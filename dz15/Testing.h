//
// Created by Nikita on 19.12.2019.
//
#pragma once

#include <random>
#include <cmath>
#include "TSP.h"


class Testing {
public:
    static double mean(std::vector<double> X);
    static double Std(std::vector<double> X, double avg);
    static void test(const std::vector<int>& points, int size);

    static std::vector<double> quality(std::vector<double> y, std::vector<double> x);
    static std::vector<std::vector<std::pair<double, double>>> generate(int points, int size);
};

