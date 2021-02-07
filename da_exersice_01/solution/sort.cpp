#include "sort.hpp"

namespace NSort {
    int CalcRank(const int maxValue, size_t size) {
        int rank = 1;
        size_t k = 2;
        while( k < (size_t)maxValue && k < size) {
            k <<= 1;
            rank++;
        }
        return rank;
    }
    int CalcMaxDigits(const int rank, int number) {
        int digits = 0;
        while(number != 0) {
            number >>= rank;
            digits++;
        }
        return digits;
    }

    void RadixSort(NVector::TVector<TKeyValue> &v)
    {
        NSort::RadixSort(v, NDate::MAX_DAYS, GetDays);
        NSort::RadixSort(v, NDate::MAX_MONTHS, GetMonths);
        NSort::RadixSort(v, NDate::MAX_YEARS, GetYears);
    }
}

