#include "solution.hpp"
const long long INF = std::numeric_limits<long long>::max();
namespace NSolution {
    long long FindShortestPath(const TGraph& g, int s, int f) {
        int n = g.size();
        std::vector<long long> dp(n, INF);
        dp[s] = 0;
        
        std::set<std::pair<int, int>> q;
        q.insert(std::make_pair(dp[s], s));
        while(!q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());

            for(int j = 0; j < (int)g[v].size(); ++j) {
                int to = g[v][j].first;
                long long len = g[v][j].second;
                if (dp[v] + len < dp[to]) {
                    q.erase(std::make_pair(dp[to], to));
                    dp[to] = dp[v] + len;
                    q.insert(std::make_pair(dp[to], to));
                }
            }
        }

        return dp[f] == INF ? -1 : dp[f];
    }
}