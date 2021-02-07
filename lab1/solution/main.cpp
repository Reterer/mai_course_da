#include <iostream>
#include "common.hpp"
#include "vector.hpp"
#include "sort.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    NVector::TVector<TKeyValue> v;
    TKeyValue kv;
    while (std::cin >> kv) {
        v.PushBack(kv);
    }

    NSort::RadixSort(v);

    for (const auto &el : v) {
        std::cout << el << '\n';
    }    
}