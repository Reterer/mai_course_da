#include <iostream>
#include "solution.hpp"

void ReadGraph(NSolution::TGraph& g, int& s, int& f) {
    int n, m;
    std::cin >> n >> m >> s >> f;
    s--;
    f--;
    g.resize(n);
    for(int i = 0; i < m; ++i) {
        int v, e, w;
        std::cin >> v >> e >> w;
        v--;
        e--;
        g[v].push_back({e, w});
        g[e].push_back({v, w});
    }
}

int main() {
    NSolution::TGraph g;

    int s, f;
    ReadGraph(g, s, f);

    long long ans = NSolution::FindShortestPath(g, s, f);
    if(ans == -1)
        std::cout << "No solution";
    else
        std::cout << ans;
    std::cout << std::endl;
    return 0;
}