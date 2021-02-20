#include "common.hpp"
#include <iomanip>
#include <cstring>

TAlpha::TAlpha(std::string::iterator& begin, const std::string::iterator& end) {
    int i = 0;
    while(i <= TAlpha::SIZE_SIGN - 1 && begin != end && *begin != ' ') {
        buf[i] = *begin;
        if(buf[i] >= 'a')
            buf[i] -= 'a' - 'A';
        ++begin;
        ++i;
    }
    buf[i] = '\0';
}

std::istream& operator>> (std::istream& in, TAlpha& alpha) {
    in >> std::setw(TAlpha::SIZE_SIGN) >> alpha.buf;

    for(int i = 0; i < TAlpha::SIZE_SIGN && alpha.buf[i] != '\0'; ++i) {
        if(alpha.buf[i] >= 'a') {
            alpha.buf[i] -= 'a' - 'A';
        }
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

namespace std {
    size_t hash<TAlpha>::operator()(const TAlpha& alpha) const {
        size_t hash_summ = 0;
        size_t p = 17;
        size_t p_pow = 1;
        for (int i = 0; i < TAlpha::SIZE_SIGN && alpha.buf[i] != '\0'; ++i) {
            hash_summ += alpha.buf[i] * p_pow;
            p_pow *= p;
        }
        return hash_summ;
    }
}