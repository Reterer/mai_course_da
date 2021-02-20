#pragma once
#include <iostream>
#include <string>

// Класс, задающий знак заданного алфавита
class TAlpha {
public:
    static const int SIZE_SIGN = 17;         // Длина знака заданного алфавита

    TAlpha(std::string::iterator& begin, const std::string::iterator& end);

    friend bool operator== (const TAlpha& a, const TAlpha& b);
    friend bool operator!= (const TAlpha& a, const TAlpha& b);
    friend bool operator< (const TAlpha& a, const TAlpha& b);

    friend std::istream& operator>> (std::istream& in, TAlpha& alpha);
    friend std::ostream& operator<< (std::ostream& out, const TAlpha& alpha);

    friend std::hash<TAlpha>;

private:
    char buf[SIZE_SIGN];                // значение знака
};

namespace std {
    template <> struct hash<TAlpha> {
        size_t operator()(const TAlpha& alpha) const;
    };
}