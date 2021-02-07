#pragma once
#include <iostream>

// Класс, задающий знак заданного алфавита
class TAlpha {
public:
    static const int SIZE_SIGN = 17;         // Длина знака заданного алфавита
    friend bool operator== (const TAlpha& a, const TAlpha& b);
    friend bool operator!= (const TAlpha& a, const TAlpha& b);
    friend bool operator< (const TAlpha& a, const TAlpha& b);

    friend std::istream& operator>> (std::istream& in, TAlpha& alpha);
    friend std::ostream& operator<< (std::ostream& out, const TAlpha& alpha);

private:
    char buf[SIZE_SIGN] = "";                // значение знака
};