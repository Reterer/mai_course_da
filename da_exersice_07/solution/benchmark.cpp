  
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "solution.hpp"

using TDuration = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

void DefaultSolution(const TMatrix& matrix) {
    int maxArray = 0;
    int n = matrix.size();
    int m = matrix[0].size();
    // Для каждой ячейки
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            // Перебираем возможные границы
            for(int h = 1; h + i <= n; ++h) {
                for(int l = 1; l + j <= m; ++l) {
                    // Проверяем, что это действительно прямоугольник из нулей
                    bool isRect = true;
                    for(int ii = 0; ii < h; ++ii) {
                        for(int jj = 0; jj < l; ++jj) {
                            if(matrix[i + ii][j + jj] != '0') {
                                isRect = false;
                                break;
                            }
                        }
                        if(!isRect)
                            break;
                    }
                    if(isRect) {
                        int array = h * l;
                        if(array > maxArray)
                            maxArray = array;
                    }
                }
            }
        }
    }

    std::cout << maxArray << std::endl;
}

void MySolution(const TMatrix& matrix) {
    std::cout << TSolution::FindLargestArea(matrix) << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    TMatrix matrix;
    ReadMatrix(matrix);

    // Тест моего алгоритма
    {
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        
        MySolution(matrix);
        
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "My Solution : " << diffTs << DURATION_PREFIX << '\n';
    }

    // Тест Наивного алгоритма
    {
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        
        DefaultSolution(matrix);
        
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "Default Solution : " << diffTs << DURATION_PREFIX << '\n';
    }

    return 0;
}