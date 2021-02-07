#pragma once
#include <stdint.h>
#include <iostream>

namespace NDate {

    // Хранит дату DD.MM.YYYY
    struct TKey {
        uint8_t Days;
        uint8_t Months;
        uint16_t Years;
        uint8_t PrintMask; // i бит означает присутствие не значащего нуля на месте DDMMYYYY

        friend std::istream & operator >> (std::istream &in,  TKey &key);
        friend std::ostream & operator << (std::ostream &out,  const TKey &key);
    };

    const uint8_t MAX_DAYS = 31;
    const uint8_t MAX_MONTHS = 12;
    const uint16_t MAX_YEARS = 9999;

    enum PrintMask : uint8_t {
        FIRST_D_IS_ZERO = 0b10000000,
        FIRST_M_IS_ZERO = 0b00100000,
        THIRD_Y_IS_ZERO = 0b00000010,
        SECOND_Y_IS_ZERO = 0b00000100,
        FIRST_Y_IS_ZERO = 0b00001000,
    };
}


// Хранит Ключ-Значение (Дата - Число)
struct TKeyValue {
    NDate::TKey Key;
    uint64_t Value;

    bool operator < (const TKeyValue b) const;

    friend std::istream & operator >> (std::istream &in,  TKeyValue &kv);
    friend std::ostream & operator << (std::ostream &out,  const TKeyValue &kv);
};

// Возвращает значение дня для элемента el
uint8_t GetDays(const TKeyValue &el);
// Возвращает значение месяца для элемента el
uint8_t GetMonths(const TKeyValue &el);
// Возвращает значение года для элемента el
uint16_t GetYears(const TKeyValue &el);