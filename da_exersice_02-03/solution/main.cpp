#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cctype>
#include <cstring>
#include <climits>
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

int main() {
    std::ios_base::sync_with_stdio(false);

    TRedBlackTree<TData, uint64_t> tr;
    char cmd;
    char path[PATH_MAX];
    TData key;
    TData mod;
    while(std::cin >> cmd) {
        switch (cmd)
        {
        case '+':
            uint64_t value;
            std::cin >> key >> value;
            if(tr.Insert(key, value))
                std::cout << "OK\n";
            else
                std::cout << "Exist\n";
            break;
        case '-':
            std::cin >> key;
            if (tr.Remove(key))
                std::cout << "OK\n";
            else
                std::cout << "NoSuchWord\n";
            break;
        case '!':
            std::cin >> mod >> path;
            try {
                if (mod == "Save")
                    TRedBlackTree<TData, uint64_t>::Save(path, tr);
                else if (mod == "Load")
                    tr = std::move(TRedBlackTree<TData, uint64_t>::Load(path));
                
                std::cout << "OK\n";
            }
            catch (const std::runtime_error& e) {
                std::cout << "ERROR: " << e.what() << '\n';
            }
            break;

        default:
            std::cin.putback(cmd);
            std::cin >> key;
            if(uint64_t* element = tr.Search(key))
                std::cout << "OK: " << *element << '\n';
            else 
                std::cout << "NoSuchWord\n"; 
            break;
        }
    }

    return 0;
}