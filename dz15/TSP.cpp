//
// Created by Nikita on 19.12.2019.
//

#include "TSP.h"

double TSP::exact_solution(const std::vector<std::pair<double, double>>& points) {
    Points = points;
    std::vector<int> permutation = std::vector<int>(points.size(), -1);
    min_path = -1;
    std::set<int> used_values;
    // Тк не важно откуда стартовать всегда будем стартовать из 0, чтобы сократить кол-во вариантов для переепрора
    used_values.insert(0);
    permutation[0] = 0;
    gen_permutation(permutation, used_values);
    return min_path;
}

void TSP::gen_permutation(std::vector<int> &permutation, std::set<int>& used_values) {

    // Ищем минимальный путь среди всех возможных
    if (used_values.size() == permutation.size()) {
        int i = 1;
        double path = 0;
        for (; i < permutation.size(); i++){
            path += distance(Points[permutation[i-1]], Points[permutation[i]]);
        }
        path += distance(Points[permutation[i-1]], Points[permutation[0]]);

        if (path < min_path || min_path == -1) {
            min_path = path;
        }

    } else {
        //Генерируем все возможные перестановки от 0 до n-1
        for (int i = 1; i < permutation.size(); i++) {
            if (!used_values.count(i)) {
                used_values.insert(i);
                permutation[used_values.size()-1] = i;
                gen_permutation(permutation, used_values);
                used_values.erase(i);
            }
        }
    }
}

std::vector<std::vector<std::pair<int, double>>> TSP::Kruskal(std::vector<Node>& graph, int n) {
    DSU dsu(n);
    std::vector<std::vector<std::pair<int, double>>> tree = std::vector<std::vector<std::pair<int, double>>>(n) ;
    std::sort(graph.begin(), graph.end());

    for (auto edge: graph) {
        if(dsu.find(edge.start) != dsu.find(edge.end)) {
            dsu.merge(edge.start, edge.end);
            tree[edge.start].push_back({edge.end, edge.weight});
            tree[edge.end].push_back({edge.start, edge.weight});
        }
    }
    return std::move(tree);
}

std::vector<int> TSP::DFS(std::vector<std::vector<std::pair<int, double>>> graph, int start) {
    std::stack<std::vector<int>> st;
    int n = graph.size();
    std::vector<bool> visited = std::vector<bool>(n, false);
    std::vector<int> path;
    st.push({start, 0});
    int time=0;

    while (!st.empty()) {
        int curr = st.top()[0], i = st.top()[1];
        path.push_back(curr);
        if (!visited[curr]) {
            visited[curr] = true;
        }

        for (; i < graph[curr].size(); ++i) {
            int next = graph[curr][i].first;
            if (!visited[next]) {
                st.top()[1] = i + 1;
                st.push({next, 0});
                break;
            }
        }
        if (i == graph[curr].size()) {
            st.pop();
        }
    }
    return path;
}

double TSP::approximate_solution(const std::vector<std::pair<double, double>>& points) {
    // Строим полный граф
    std::vector<Node> graph;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            double weight = distance(points[i], points[j]);
            graph.push_back({i, j, weight});
        }
    }

    std::vector<std::vector<std::pair<int, double>>> tree = Kruskal(graph, points.size());
    std::vector<int> end_path, path = DFS(tree, 0);
    for (int vertex_1: path) {
        bool flag = true;
        for (int vertex_2: end_path) {
            if (vertex_1 == vertex_2) {
                flag = false;
                break;
            }
        }
        if (flag) {
            end_path.push_back(vertex_1);
        }
    }

    double path_size = 0;
    int i = 0;
    for (; i < end_path.size(); i++) {
        path_size += distance(points[end_path[i-1]], points[end_path[i]]);
    }
    path_size += distance(points[end_path[i-1]], points[end_path[0]]);
    return path_size;
}

