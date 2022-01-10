#pragma once
#include <vector>
#include <set>
#include <limits>

namespace NSolution {
    using TGraph = std::vector<std::vector<std::pair<int, int>>>;
    // return len of the shortest path
    // -1 if path is not exist
    long long FindShortestPath(const TGraph& g, int s, int f);

}
