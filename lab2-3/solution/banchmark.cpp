#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cctype>
#include <cstring>
#include <climits>

#include <chrono>
#include <map>

#include "rbtree.hpp"

struct TData {
    static const int MAX_STRING_LEN = 257;
    char buf[MAX_STRING_LEN];

    TData() {
        for(int i = 0; i < MAX_STRING_LEN; ++i)
            buf[i] = 0;
    }
    
    TData(const TData& data) {
        for(int i = 0; i < MAX_STRING_LEN; ++i) {
            buf[i] = data.buf[i];
        }
    }

    bool operator== (const TData& data) const {
        return operator==(data.buf);
    }

    bool operator== (const char* str) const {
        for(int i = 0; i < MAX_STRING_LEN; ++i) {
            char a = std::tolower(buf[i]);
            char b = std::tolower(str[i]);

            if(a == '\0' && b == '\0')
                return true;
            if(a != b)
                return false;
        }
        return true;
    }

    bool operator!= (const TData& data) const {
        return !(*this == data);
    }

    bool operator< (const TData& data) const {
        for(int i = 0; i < MAX_STRING_LEN; ++i) {
            char a = std::tolower(buf[i]);
            char b = std::tolower(data.buf[i]);

            if(b == '\0')
                return false;
            if(a == '\0')
                return true;
            if(a < b)
                return true;
            else if (a > b)
                return false;
        }
        return false;
    }
    
    friend std::istream& operator>> (std::istream& in, TData& data) {
        in >> std::setw(MAX_STRING_LEN) >> data.buf;
        return in;
    }

    friend std::ostream& operator<< (std::ostream& out, const TData& data) {
        out << data.buf;
        return out;
    }
};

void BanchMyTree(std::istream& in) {
    TRedBlackTree<TData, uint64_t> tr;
    char cmd;
    TData key;
    TData mod;
    while(in >> cmd) {
        switch (cmd)
        {
        case '+':
            uint64_t value;
            in >> key >> value;
            if(tr.Insert(key, value))
                std::cout << "OK\n";
            else
                std::cout << "Exist\n";
            break;
        case '-':
            in >> key;
            if (tr.Remove(key))
                std::cout << "OK\n";
            else
                std::cout << "NoSuchWord\n";
            break;
        default:
            in.putback(cmd);
            in >> key;
            if(uint64_t* element = tr.Search(key))
                std::cout << "OK: " << *element << '\n';
            else 
                std::cout << "NoSuchWord\n"; 
            break;
        }
    }
}

void BanchMap(std::istream& in) {
    std::map<TData, uint64_t> tr;
    char cmd;
    TData key;
    TData mod;
    while(in >> cmd) {
        switch (cmd)
        {
        case '+':
            uint64_t value;
            in >> key >> value;
            {
                auto p = tr.insert(std::make_pair(key, value));
                if(p.second)
                    std::cout << "OK\n";
                else
                    std::cout << "Exist\n";
            }
            break;
        case '-':
            in >> key;
            if (tr.erase(key))
                std::cout << "OK\n";
            else
                std::cout << "NoSuchWord\n";
            break;
        default:
            in.putback(cmd);
            in >> key;
            {
                auto element = tr.find(key);
                if(element != tr.end())
                    std::cout << "OK: " << element->second << '\n';
                else 
                    std::cout << "NoSuchWord\n";
            }             
            break;
        }
    }
}

using TDuration = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);

    if(argc != 2)
        return 1;

    // Тест моего дерева
    {
        std::ifstream ifs(argv[1]);
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        BanchMyTree(ifs);
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "My Tree : " << diffTs << DURATION_PREFIX << '\n';
    }

    // Тест стандартной реализации
    {
        std::ifstream ifs(argv[1]);
        std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
        BanchMap(ifs);
        auto endTs = std::chrono::system_clock::now();
        uint64_t diffTs = std::chrono::duration_cast<TDuration>( endTs - startTs ).count();
        std::cerr << "STL map : " << diffTs << DURATION_PREFIX << '\n';
    }

    return 0;
}