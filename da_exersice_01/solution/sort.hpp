#pragma once
#include <stdint.h>
#include "common.hpp"
#include "vector.hpp"

namespace NSort {
    // Сортировка подсчетом
    // Сортирует вектор v по ключу, который возвращает функцию getKey
    // MAX_VALUE - максимальное значение ключа
    template <class T, class K>
    void CountSort(NVector::TVector<T> &v, K (*getKey)(const T&), const int rank, const int digit) {
        NVector::TVector<T> sorted(v.GetSize());
        int base = 1 << rank;
        int mask = (1 << rank) - 1;
        int shift = rank * digit;
        int64_t *count = new int64_t[base];

        // Обнуляем count
        for(int64_t i = 0; i < base; ++i) {
            count[i] = 0;
        }

        // Считаем кол-во повторов каждого элемента
        for(int64_t i = 0; i < (int64_t)v.GetSize(); ++i) {
            count[(getKey(v[i]) >> shift) & mask]++;
        }

        // Считаем кол-во элементов меньших или равных 
        for(int64_t i = 1; i < base; ++i) {
            count[i] += count[i-1];
        }

        // Создаем отсортированный массив
        for(int64_t i = v.GetSize() - 1; i >= 0; --i) {
            sorted[count[(getKey(v[i]) >> shift) & mask] - 1] = v[i];
            count[(getKey(v[i]) >> shift) & mask]--;
        }

        // копируем новый массив в старый
        NVector::TVector<T>::Swap(v, sorted);

        delete[] count;
    }


    // Вычисляет оптимальную двоичную степень основания системы счисления
    int CalcRank(const int maxValue, const size_t size);
    // Вычисляет максимальное кол-во разрядов в системе счисления 2^rank в числе number
    int CalcMaxDigits(const int rank, int number);

    // Поразрядная сортировка для вектора TKeyValue
    template<class T, class K>
    void RadixSort(NVector::TVector<T> &v, const int maxValue, K (*getKey)(const T&)) {
        int rank = CalcRank(maxValue, v.GetSize());
        int digits = CalcMaxDigits(rank, maxValue);
        for (int digit = 0; digit < digits; ++digit) {
            CountSort(v, getKey, rank, digit);
        }
    }

    // Сортирует вектор типа Ключ-Значение
    void RadixSort(NVector::TVector<TKeyValue> &v);
}