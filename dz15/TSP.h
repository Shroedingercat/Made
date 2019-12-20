//
// Created by Nikita on 19.12.2019.
//
#pragma once

#include <cmath>
#include <utility>
#include <vector>
#include <set>
#include <stack>
#include "DSU.h"

struct Node {
    int start;
    int end;
    double weight;
    Node() : start(-1), end(-1), weight(0) {};
    Node(int start_, int end_, int weight_) : start(start_), end(end_),  weight(weight_) {};

    bool operator<(const Node& other) const{
        return weight < other.weight;
    }
    bool operator>(const Node& other) const{
        return weight > other.weight;
    }
};

class TSP {
public:
    TSP() : Points({}), min_path(-1){};

    double exact_solution(const std::vector<std::pair<double, double>>& points);
    // Евклидово расстояние
    static double distance(const std::pair<double, double>& f, const std::pair<double, double>& s) {
        return std::sqrt(std::pow((f.first - s.first), 2) + std::pow((f.second - s.second), 2));
    }
    double approximate_solution(const std::vector<std::pair<double, double>>& points);
    // поиск минимального остовного дерева методом Крускала
    static std::vector<std::vector<std::pair<int, double>>> Kruskal(std::vector<Node>& graph, int n);
    // Нерекурсивный обход в глубину
    std::vector<int> DFS(std::vector<std::vector<std::pair<int, double>>> graph, int start);

private:
    void gen_permutation(std::vector<int>& permutation, std::set<int>& used_values);
    std::vector<std::pair<double, double>> Points;
    double min_path;
};



