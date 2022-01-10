#include "solution.hpp"
#include <iostream>

int main() {

    TGrid grid;
    int n,m;
    std::cin >> n >> m;
    grid.resize(n);
    for(int i = 0; i < n; ++i) {
        grid[i].resize(m);
        for(int j = 0; j < m; ++j) {
            std::cin >> grid[i][j];
        }
    }

    int q;
    std::cin >> q;
    for(int i = 0; i < q; ++i) {
        TPoint s,f;
        std::cin >> s.first >> s.second >> f.first >> f.second;
        s.first--;
        s.second--;
        f.first--;
        f.second--;
        std::cout << Find(grid, s, f) << std::endl;
    }

    return 0;
}