#pragma once
#include <vector>
#include <algorithm>

struct TSegment {
    int left;
    int right;
    int i;
};

std::vector<TSegment> Solution(const std::vector<TSegment>& list, int m);