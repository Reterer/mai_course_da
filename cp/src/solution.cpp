#include "solution.hpp"
#include <set>
#include <iostream>

void Print(const TGrid& grid, const std::vector<std::vector<long long>>& costs) {
    int n = grid.size();
    int m = grid[0].size();
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                std::cout << (costs[i][j] == INF ? -1 : costs[i][j]) << '\t';
            }
            else {
                std::cout << grid[i][j] << '\t';
            }
        }
        std::cout << "\n";
    }
}

inline long long Heuristic(const TPoint& start, const TPoint& finish) {
    return abs(start.first - finish.first) + abs(start.second - finish.second);
}

long long Find(const TGrid& grid, const TPoint& start, const TPoint& finish) {
    int n = grid.size();
    int m = grid[0].size();
    std::vector<std::vector<long long>> costs(n, std::vector<long long>(m, INF));
    costs[start.first][start.second] = 0;
    
    std::set<std::pair<int, TPoint>> q;

    q.insert(std::make_pair(0, start));
    while(!q.empty()) {
        TPoint v = q.begin()->second;
        q.erase(q.begin());
        if (v == finish)
            break;

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for(int i = 0; i < 4; ++i) {
            TPoint to = {v.first + dx[i], v.second + dy[i]};
            if (to.first < 0 || to.first >= n || to.second < 0 || to.second >= m)
                continue;
            if (grid[to.first][to.second] != '.' && grid[to.first][to.second] != 'G')
                continue;

            if (costs[v.first][v.second] + 1 < costs[to.first][to.second]) {
                long long heruisticLen = Heuristic(finish, to);
                q.erase(std::make_pair(costs[to.first][to.second] + heruisticLen, to));
                costs[to.first][to.second] = costs[v.first][v.second] + 1;
                q.insert(std::make_pair(costs[to.first][to.second] + heruisticLen, to));
            }
        }
    }
    return costs[finish.first][finish.second] == INF ? -1 : costs[finish.first][finish.second];
}