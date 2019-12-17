/*
 * Ребро неориентированного графа называется мостом, если удаление этого ребра из графа увеличивает число компонент связности.
 * Дан неориентированный граф, требуется найти в нем все мосты.
 */
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
 
typedef std::vector<std::vector<std::pair<int, int>>> adjacency_lst;
 
void dfs(const adjacency_lst& graph, std::vector<int>& bridges, std::vector<bool>& visited, int n, int start) {
    std::stack<std::vector<int>> st;
    std::vector<int> entry = std::vector<int>(n, 0), lowest = std::vector<int>(n, -1);
    st.push({start, -1, 0});
    int time=0;
 
    while (!st.empty()) {
        int curr = st.top()[0], parent = st.top()[1], i = st.top()[2];
 
        if (!visited[curr]) {
            entry[curr] = lowest[curr] = time++;
            visited[curr] = true;
        }
 
        if (i != 0) {
            int next = graph[curr][i-1].first;
            bool dbl = false;
            lowest[curr] = std::min(lowest[curr], lowest[next]);
            for (int j = 0; j < graph[next].size(); j++){
                for (int l = j + 1; l < graph[curr].size(); l++) {
                    if (graph[next][l].first == graph[curr][j].first) {
                        dbl = true;
                    }
                }
            }
            if (lowest[next] > entry[curr] && !dbl) {
                bridges.push_back(graph[curr][i-1].second);
            }
        }
 
        for (; i < graph[curr].size(); ++i) {
            int next = graph[curr][i].first;
            if (next == parent) {
                continue;
            }
            if (visited[next]) {
                lowest[curr] = std::min(lowest[curr], entry[next]);
            } else {
                st.top()[2] = i + 1;
                st.push({next, curr, 0});
                break;
            }
        }
        if (i == graph[curr].size()) {
            st.pop();
 
        }
    }
 
}
 
std::vector<int> find_bridges(const adjacency_lst& graph, int n) {
    std::vector<int> bridges;
    std::vector<bool> visited = std::vector<bool>(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(graph, bridges, visited, n, i);
        }
    }
    return std::move(bridges);
}
 
int main() {
    int n=0, m=0, u=0, w=0;
    std::fstream inOut;
    inOut.open("bridges.in", std::ios::in);
    inOut >> n >> m;
    adjacency_lst graph = adjacency_lst(n);
 
    for (int i = 0; i < m; i++) {
        inOut >> u >> w;
        u--;
        w--;
        // w - смежная вершина к u, i - номер ребра
        graph[u].push_back({w, i+1});
        graph[w].push_back({u, i+1});
    }
    inOut.close();
    inOut.open("bridges.out", std::ios::out);
    std::vector<int> bridges = find_bridges(graph, n);
    std::sort(bridges.begin(), bridges.end());
    inOut << bridges.size() << std::endl;
 
    for (auto bridge: bridges) {
        inOut << bridge <<std::endl;
    }
    inOut.close();
    return 0;
}