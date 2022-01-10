#pragma once
#include <vector>
#include <limits>

const long long INF = std::numeric_limits<long long>::max();
typedef std::vector<std::vector<char>> TGrid;
typedef std::pair<int,int> TPoint;

long long Find(const TGrid& grid, const TPoint& start, const TPoint& finish);