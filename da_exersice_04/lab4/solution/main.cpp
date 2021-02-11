#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

#include "common.hpp"
#include "algorithm.hpp"



int main() {
    std::vector<TAlpha> pattern;
    {
        // Чтение паттерна
        while(std::cin.peek() != '\n') {
            TAlpha alpha;
            std::cin >> alpha;
            pattern.push_back(alpha);
        }
        std::cin.get(); // Считываем \n
    }

    TSubstringFinder(pattern, std::cin).Find();
    return 0;
}