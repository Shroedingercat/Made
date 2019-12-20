//
// Created by Nikita on 19.12.2019.
//

#include "Testing.h"

double Testing::mean(std::vector<double> X) {
    double avg = 0;
    for(auto x: X) {
        avg += x;
    }
    avg /= X.size();
    return avg;
}

double Testing::Std(std::vector<double> X, double avg) {
    double out = 0;
    for (double x : X) {
        out += std::pow(x - avg, 2);
    }
    out /= X.size();
    return out;
}

std::vector<double> Testing::quality(std::vector<double> y, std::vector<double> x) {
    assert(y.size() == x.size());
    std::vector<double> out;
    for (int i = 0; i < y.size(); i++) {
        out.push_back(x[i]/y[i]);
    }
    return out;
}

std::vector<std::vector<std::pair<double, double>>> Testing::generate(int points, int size) {
    // генерация точек из нормального распределения при помощи преобразования Бокса-Мюллера
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distribution(0,1);
    std::vector<std::vector<std::pair<double, double>>> samples;
    for (int i = 0; i < size; i++) {
        samples.emplace_back();
        for (int j = 0; j < points; j++) {
            double f = distribution(gen), r = distribution(gen);
            double x = std::cos(2 * 3.14 * f) * std::sqrt(-2 * std::log(r));
            double y = std::sin(2 * 3.14 * f) * std::sqrt(-2 * std::log(r));
            samples[i].push_back({x, y});
        }
    }
    return samples;
}

void Testing::test(const std::vector<int>& points, int size) {
    TSP tsp;
    std::vector<std::vector<double>> paths;
    for (auto point: points) {
        std::vector<std::vector<std::pair<double, double>>> samples = generate(point, size);
        std::vector<double> paths_ex, paths_apr;
        for (auto sample: samples) {
            paths_ex.push_back(tsp.exact_solution(sample));
            paths_apr.push_back(tsp.approximate_solution(sample));
        }
        double avg = mean(quality(paths_ex, paths_apr));
        paths.push_back({avg,  Std(quality(paths_ex, paths_apr), avg)});
    }
    std::cout << "Среднее качество    "<< "Среднеквадратичное отклонение" << std::endl;
    for (auto mms: paths) {
        std::cout << mms[0] << "                    " << mms[1] << std::endl;
    }
}