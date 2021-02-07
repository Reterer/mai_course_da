#include <iostream>
#include <algorithm>
#include <chrono>

#include "sort.hpp"
#include "vector.hpp"
#include "common.hpp"


using TDuration = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

// using TDuration = std::chrono::milliseconds;
// const std::string DURATION_PREFIX = "ms";

int main()
{
    NVector::TVector<TKeyValue> input, inputStl;
    TKeyValue kv;
    while (std::cin >> kv)
    {
        input.PushBack(kv);
        inputStl.PushBack(kv);
    }

    std::cout << "Count of lines is " << input.GetSize() << std::endl;

    // Измеряем время работы поразрядной сортировки.
    std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
    NSort::RadixSort(input);
    auto endTs = std::chrono::system_clock::now();
    uint64_t radixSortTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();

    // Измеряем время работы stl сортировки.
    startTs = std::chrono::system_clock::now();
    std::stable_sort(std::begin(inputStl), std::end(inputStl));
    endTs = std::chrono::system_clock::now();

    uint64_t stl_sort_ts = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
    std::cout << "Radix sort time: " << radixSortTs << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;
}