#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "solution.hpp"

using TDuration = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

int takedSegments = 0;
int helper (const std::vector<TSegment>& list, int n, int m, int maxRight) {
    if(n == (int)list.size()) {
        if(maxRight >= m)
            return takedSegments;
        else 
            return 0;
    }
    // Если не используем текущую ноду
    int fans = helper(list, n + 1, m, maxRight);

    // Если используем текущую ноду
    int sans = 0;
    if(maxRight >= list[n].left) {
        takedSegments++;
        sans = helper(list, n + 1, m, std::max(maxRight, list[n].right));
        takedSegments--;
    }
    else {
        // Мы не можем взять ее
    }
    if(fans == 0)
        return sans;
    if(sans == 0)
        return fans;
    return std::min(sans, fans);
}

void DefaultSolution(const std::vector<TSegment>& list, int m) {
    std::vector<TSegment> sortedList(list.begin(), list.end());
    std::sort(sortedList.begin(), sortedList.end(), [](TSegment& lhs, TSegment& rhs){
        if(lhs.left < rhs.left)
            return true;
        return lhs.left == rhs.left && lhs.right < rhs.right;
    });

    std::cout << helper(sortedList, 0, m, 0) << std::endl;
}

void MySolution(const std::vector<TSegment>& list, int m) {
    std::vector<TSegment> ans = Solution(list, m);
    std::cout << ans.size() << '\n';
    // for(auto& el : ans) {
    //     std::cout << el.left << ' ' << el.right << '\n';
    // }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int m;
    int n;
    std::cin >> n;
    std::vector<TSegment> list(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> list[i].left >> list[i].right;
        list[i].i = i;
    }
    std::cin >> m;

    // Тест моего алгоритма
    {
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        
        MySolution(list, m);
        
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "My Solution : " << diffTs << DURATION_PREFIX << '\n';
    }

    // Тест Наивного алгоритма
    {
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        
        DefaultSolution(list, m);
        
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "Default Solution : " << diffTs << DURATION_PREFIX << '\n';
    }

    return 0;
}