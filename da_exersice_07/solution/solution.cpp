#include "solution.hpp"

int TSolution::FindLargestArea(const TMatrix& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    std::vector<std::vector<TRectInfo>> dp(n, 
            std::vector<TRectInfo>(m, {0,0,m}));

    int maxArray = 0;
    for(int i = 0; i < n; ++i) {
        int Start = 0; // Начало последовательности нулей
        for(int j = 0; j < m; ++j) {
            if(i > 0)
                dp[i][j] = dp[i-1][j];
            
            if(matrix[i][j] == '0') {
                dp[i][j].Height++;
                dp[i][j].Start = std::max(Start, dp[i][j].Start);
            }
            else {
                dp[i][j].Height = 0;
                dp[i][j].Start = 0;
                Start = j + 1;
            }
        }

        // Вычисляем конец последовательностей и площади
        int End = m;
        for(int j = m-1; j >= 0; --j) {
            if(matrix[i][j] == '0') {
                dp[i][j].End = std::min(End, dp[i][j].End);
            }
            else {
                dp[i][j].End = m;
                End = j;
            }
            
            int array = dp[i][j].Height * (dp[i][j].End - dp[i][j].Start);
            if(array > maxArray)
                maxArray = array;
        }
    }

    return maxArray;
}

void ReadMatrix(TMatrix& matrix) {
    int n,m;
    std::cin >> n >> m;
    matrix.resize(n);

    for(int i = 0; i < n; ++i) {
        matrix[i].resize(m);
        for(int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

