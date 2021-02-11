#include <map>
#include "algorithm.hpp"


TSubstringFinder::TSubstringFinder(std::vector<TAlpha>& pattern, std::istream& textStream) 
    : pattern(pattern), textStream(textStream)
{}

void TSubstringFinder::Find() {
    PreprocessBadChar();
    PreprocessGoodSuffix();
    ReadText();

    int currLine = 0;
    size_t k = pattern.size() - 1;
    while(k < text.size()) {
        int j = pattern.size() - 1;
        int i = k;

        // SkipElements(k, i, j);
        while(j >= 0 && text[i] == pattern[j]) {
            // std::cout << k << ' ' << i << ' ' << j << '\n';
            --i;
            --j;
        }
        if(j == -1) {
            while(linesNumber[currLine] <= k - pattern.size() + 1)
                ++currLine;
            int word = k - pattern.size() - linesNumber[currLine-1] + 2;
            std::cout << currLine << ", " << word << '\n';
            ++k; // Переходим к следующему слову
        }
        else {
            int shift = 1;
            // Проверяем правило плохого символа
            shift = std::max(shift, GetShiftBadChar(i, j));
            // std::cout << "shift bad char: " << GetShiftBadChar(i, j) << "\n";
            // Проверяем правило хорошего суффикса
            shift = std::max(shift, GetShiftGoodSuffix(i, j));
            // std::cout << "shift good suffix " << GetShiftGoodSuffix(i, j) << "\n";

            k += shift;
        }
    }
}

int TSubstringFinder::GetShiftBadChar(int i, int j) {
    auto mapEl = badChar.find(text[i]);
    // Если знака нет в паттерне
    if(mapEl == badChar.end()) {
        // std::cout << "bch no in: " << j + 1 << '\n'; 
        return j + 1; // Двигаем паттерн за текущий элемент
    }

    auto begin = mapEl->second.begin();
    auto end = mapEl->second.end();
    auto it = std::lower_bound(begin, end, j);
    if(it == end) {
        --it; // В массиве всегда есть минимум 1 элемент
    }
    else if(*it >= j && end - begin > 1) {
        --it; // Если есть куда двигаться
    }
    else {
        // std::cout << "bch no less: " << j + 1 << '\n'; 
        return j + 1; // Нет элемента в левой части паттерна => двигаем паттерн за текущий элемент
    }

    return j - *it; // Двигаем паттерн так, что бы на этом же месте остался такой же знак
}

int TSubstringFinder::GetShiftGoodSuffix(int i, int j) {
    int shift = 0;
    if(j + 1 < pattern.size()) {
        if(LFunction[j + 1] > 0)
            shift = pattern.size() - LFunction[j+1] - 1;
        else
            shift = pattern.size() - lFunction[j+1] - 1;
    }
    return shift;
}

void TSubstringFinder::SkipElements(int k, int& i, int& j) {
    while(j >= 0) {
        if(mFunction[i] == 0||(mFunction[i] == nFunction[j] && nFunction[j] == 0)) {
            if(pattern[j] == text[i]) {
                if(j == 0) {
                    mFunction[k] = pattern.size();
                    --i;
                    --j;
                    return;
                }
                else {
                    --i;
                    --j;
                }
            }
            else {
                mFunction[k] = k - i;
                return;
            }
        }
        else if(mFunction[i] < nFunction[j]) {
            i -= mFunction[i];
            j -= mFunction[i];
        }
        else if(mFunction[i] >= nFunction[j] && nFunction[j] == j+1) {
            mFunction[k] = k - i;
            j -= nFunction[j];
            i -= nFunction[j];
            return;
        }
        else if(mFunction[i] > nFunction[j] &&  nFunction[j] < j+1) {
            mFunction[k] = k - i;
            j -= nFunction[j];
            i -= nFunction[j];
            return;
        }
        else if(mFunction[i] == nFunction[j], nFunction[j] < j+1) {
            i -= mFunction[i]; 
            j -= mFunction[i];
        }
    }
}

void TSubstringFinder::PreprocessBadChar() {
    for(int i = 0; i < pattern.size(); ++i) {
        auto res = badChar.insert(std::make_pair(pattern[i], std::vector<int>()));
        res.first->second.push_back(i);
    }

    // for(auto& kv : badChar) {
    //     std::cout << kv.first << ": ";
    //     for(auto idx : kv.second) {
    //         std::cout << idx << ' ';
    //     } std::cout << '\n';
    // }
}

void TSubstringFinder::PreprocessGoodSuffix() {
    nFunction.resize(pattern.size());
    for(int i = pattern.size()-2, k = pattern.size()-1; i >= 0; --i) {
        int l = k - nFunction[k] + 1;
        if(i >= l) {
            nFunction[i] = std::min(nFunction[pattern.size() - k + i - 1], i - l + 1);
        }
        
        while(i - nFunction[i] >= 0 && pattern[i - nFunction[i]] == pattern[pattern.size() - nFunction[i] - 1]) {
            nFunction[i]++;
        }
        
        if(i - nFunction[i] < l)
            k = i;
    }
    
    LFunction.resize(pattern.size(),0);
    lFunction.resize(pattern.size()+1, 0);
    // for(ssize_t i = pattern.size() - 1; i >= 0; --i) {
    //     ssize_t len = pattern.size() - i;
    //     ssize_t j = len - 1;
    //     if(nFunction[j] == len){
    //         lFunction[i] = j;
    //     }
    //     else if (i + 1 < pattern.size())
    //         lFunction[i] = lFunction[i+1];
    //     std::cout << i << ' ' << len << ' ' << nFunction[j] << ' ' << j << ' ' << lFunction[i] << '\n';
    // }

    for(ssize_t i = 0; i < pattern.size(); ++i) {
        if(nFunction[i] != 0) {
            ssize_t j = pattern.size() - nFunction[i];
            LFunction[j] = i;
        }
        ssize_t j = pattern.size() - i - 1;
        if(nFunction[i] == i + 1) {
            lFunction[j] = i + 1;
        }
        else {
            lFunction[j] = lFunction[j+1];                        
        }
    }

    // std::cout << "nFunction\n";
    // for(auto el : nFunction) {
    //     std::cout << el << ' ';
    // } std::cout << '\n';
    // std::cout << "lFunction\n";
    // for(auto el : lFunction) {
    //     std::cout << el << ' ';
    // } std::cout << '\n';
    // std::cout << "LFunction\n";
    // for(auto el : LFunction) {
    //     std::cout << el << ' ';
    // } std::cout << '\n';
}

void TSubstringFinder::ReadText() {
    int wordNumber = 0;
    linesNumber.push_back(0);
    while(!textStream.eof() && textStream.peek() != '\n'){
        TAlpha alpha;
        textStream >> alpha;
        text.push_back(alpha);
        // std::cout << alpha << ' ';
        wordNumber++;
        if(textStream.peek() == '\n') {
            linesNumber.push_back(wordNumber);
            textStream.get(); // Считываем '\n'
        }
    }
    linesNumber.push_back(wordNumber);
    mFunction.resize(text.size());
}