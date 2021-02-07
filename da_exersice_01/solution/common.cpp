#include "common.hpp"

namespace NDate {
    int ReadNumber(std::istream &in, int &zeroPrefixCount) {
        zeroPrefixCount = 0;

        int ch;
        // считываем разделитель
        while ((ch = in.get()) == ' ' || ch == '\n' || ch == '\t') {
            ;
        }
        in.putback(ch);
        // считываем лидирующие нули
        while ((ch = in.get()) == '0') {
            zeroPrefixCount++;
        }
        in.putback(ch);
        
        if(ch == '.' || ch == ' ') {
            return 0;
        }

        // считываем остаток числа
        int res;
        in >> res;

        return res;
    }

    std::istream & operator >> (std::istream &in,  TKey &key) {
        char dot;
        int zeroPrefixCount = 0;
        
        key.PrintMask = 0;

        key.Days = ReadNumber(in, zeroPrefixCount);
        in >> dot;
        if (zeroPrefixCount >= 1) {
            key.PrintMask |= PrintMask::FIRST_D_IS_ZERO;
        }

        key.Months = ReadNumber(in, zeroPrefixCount);
        in >> dot;
        if (zeroPrefixCount >= 1) {
            key.PrintMask |= PrintMask::FIRST_M_IS_ZERO;
        }

        key.Years = ReadNumber(in, zeroPrefixCount);
        if (zeroPrefixCount >= 3) {
            key.PrintMask |= PrintMask::THIRD_Y_IS_ZERO;
        }
        else if (zeroPrefixCount == 2) {
            key.PrintMask |= PrintMask::SECOND_Y_IS_ZERO;
        }
        else if (zeroPrefixCount == 1) {
            key.PrintMask |= PrintMask::FIRST_Y_IS_ZERO; 
        }

        return in;
    }
    
    std::ostream & operator << (std::ostream &out,  const TKey &key) {
        if (key.PrintMask & PrintMask::FIRST_D_IS_ZERO) {
            out << '0';
        }        
        out << (int)key.Days << '.' ;
        
        if (key.PrintMask & PrintMask::FIRST_M_IS_ZERO) {
            out << '0';
        }
        out << (int)key.Months << '.';
        
        if (key.PrintMask & PrintMask::THIRD_Y_IS_ZERO) {
            out << "000";
        }
        else if (key.PrintMask & PrintMask::SECOND_Y_IS_ZERO) {
            out << "00";
        }
        else if (key.PrintMask & PrintMask::FIRST_Y_IS_ZERO) {
            out << '0';
        }
        out << (int)key.Years;
        
        return out;
    }
}

std::istream & operator >> (std::istream &in,  TKeyValue &kv) {
    in >> kv.Key >> kv.Value;
    return in;
}
std::ostream & operator << (std::ostream &out,  const TKeyValue &kv) {
    out << kv.Key << ' ' << kv.Value;
    return out;
}

bool TKeyValue::operator < (const TKeyValue b) const {
    if (Key.Years != b.Key.Years) {
        return Key.Years < b.Key.Years;
    }
    if (Key.Months != b.Key.Months) {
        return Key.Months < b.Key.Months;
    }

    return Key.Days < b.Key.Days;
}

uint8_t GetDays(const TKeyValue &el) {
    return el.Key.Days;
}
uint8_t GetMonths(const TKeyValue &el) {
    return el.Key.Months;
}
uint16_t GetYears(const TKeyValue &el) {
    return el.Key.Years;
}
