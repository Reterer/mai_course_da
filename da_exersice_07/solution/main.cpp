#include <iostream>
#include <vector>

#include "solution.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    TMatrix matrix;
    ReadMatrix(matrix);
    std::cout << TSolution::FindLargestArea(matrix) << std::endl;
    return 0;
}