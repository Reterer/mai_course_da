#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "solution.hpp"

using TDuration = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

long long helper(int curr, int f, std::vector<char>& used, NSolution::TGraph& g) {
    const long long INF = std::numeric_limits<long long>::max();
    if(curr == f)
        return 0;

    long long ans = INF;
    used[curr] = true;
    for(auto& edge : g[curr]) {
        if(!used[edge.first]) {
            long long ansHelper = helper(edge.first, f, used, g);
            if(ansHelper < INF) {
                ans = std::min(ans, ansHelper + edge.second);
            }
        }
    }
    used[curr] = false;

    return ans;
}

void DefaultSolution(NSolution::TGraph& g, int s, int f) {
    std::vector<char> used(g.size(), false);
    std::cout << helper(s, f, used, g) << std::endl;
}

void MySolution(NSolution::TGraph& g, int s, int f) {
    std::cout << NSolution::FindShortestPath(g, s, f) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, m, s, f;
    std::cin >> n >> m >> s >> f;
    NSolution::TGraph g(n);
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
    // Тест моего алгоритма
    {
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        
        MySolution(g, s, f);
        
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "My Solution : " << diffTs << DURATION_PREFIX << '\n';
    }

    // Тест Наивного алгоритма
    {
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        
        DefaultSolution(g, s, f);
        
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "Default Solution : " << diffTs << DURATION_PREFIX << '\n';
    }

    return 0;
}