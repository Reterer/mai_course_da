#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

#include "common.hpp"
#include "algorithm.hpp"



int main() {
    std::ios_base::sync_with_stdio(false);
    
    std::vector<TAlpha> pattern;
    {
        std::string pstr;
        std::getline(std::cin, pstr);
        auto it = pstr.begin();
        while(it != pstr.end()) {
            if(*it == ' ') {
                ++it;
                continue;
            }
            pattern.push_back(TAlpha(it, pstr.end()));
        }
    }

    std::vector<std::pair<int, int> > entries = FindApoGian(pattern, std::cin);
    for (auto entry : entries) {
        std::cout << entry.first << ", " << entry.second << '\n';
    }
    
    return 0;
}