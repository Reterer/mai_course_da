#include "common.hpp"
#include <iomanip>
#include <cstring>

std::istream& operator>> (std::istream& in, TAlpha& alpha) {
    in >> std::setw(TAlpha::SIZE_SIGN) >> alpha.buf;
    
    for (char& ch : alpha.buf) {
        ch = std::tolower(ch);
    }

    return in;
}

std::ostream& operator<< (std::ostream& out, const TAlpha& alpha) {
    out << alpha.buf;
    return out;
}

bool operator== (const TAlpha& a, const TAlpha& b) {
    return std::strcmp(a.buf, b.buf) == 0;
}

bool operator!= (const TAlpha& a, const TAlpha& b) {
    return std::strcmp(a.buf, b.buf) != 0;
}


bool operator< (const TAlpha& a, const TAlpha& b) {
    return std::strcmp(a.buf, b.buf) < 0;
}
