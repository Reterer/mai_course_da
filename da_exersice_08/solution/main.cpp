#include <iostream>
#include <vector>
#include <algorithm>
#include "solution.hpp"

int main() {
    int n, m;
    
    std::cin >> n;
    std::vector<TSegment> list(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> list[i].left >> list[i].right;
        list[i].i = i;
    }
    std::cin >> m;

    std::vector<TSegment> ans = Solution(list, m);
    std::cout << ans.size() << '\n';
    for(auto& el : ans) {
        std::cout << el.left << ' ' << el.right << '\n';
    }
    return 0;
}