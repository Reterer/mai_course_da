#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#include "common.hpp"
#include "algorithm.hpp"

using TDuration = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

void BenchMyAlgo(std::istream& in) {
    std::vector<TAlpha> pattern;
    {
        std::string pstr;
        std::getline(in, pstr);
        auto it = pstr.begin();
        while(it != pstr.end()) {
            if(*it == ' ') {
                ++it;
                continue;
            }
            pattern.push_back(TAlpha(it, pstr.end()));
        }
    }

    std::vector<std::pair<int, int> > entries = FindApoGian(pattern, in);
    std::cout << entries.size() << '\n';
}

void BenchSTDAlgo(std::istream& in) {
    std::string pattern;
    std::string text;

    std::getline(in, pattern);
    std::getline(in, text);

    int j  = 0;
    for (std::size_t i = text.find(pattern); i != std::string::npos; i = text.find(pattern, i + 1)) {
        j++;
    }
    std::cout << j << '\n';
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);

    if(argc != 2)
        return 1;

    // Тест моего алгоритма
    {
        std::ifstream ifs(argv[1]);
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        
        BenchMyAlgo(ifs);
        
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "My Serach : " << diffTs << DURATION_PREFIX << '\n';
    }

    // Тест стандартного алгоритма
    {
        std::ifstream ifs(argv[1]);
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        
        BenchSTDAlgo(ifs);
        
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "STL Search : " << diffTs << DURATION_PREFIX << '\n';
    }

    return 0;
}