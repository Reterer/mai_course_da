#include <unordered_map>
#include "algorithm.hpp"

void ReadText(std::istream& input, std::vector<TAlpha>& text, std::vector<int>& linesNumber) {    
    int wordNumber = 0;
    linesNumber.push_back(0);
    std::string str;
    while(std::getline(input, str)) {
        std::string::iterator it = str.begin();
        while(it != str.end()) {
            if(*it == ' ') {
                ++it;
                continue;
            }
            text.push_back(TAlpha(it, str.end()));
            wordNumber++;
        }
        linesNumber.push_back(wordNumber);
    }
    linesNumber.push_back(wordNumber);
}

std::unordered_map<TAlpha, std::vector<int> > PreprocessBadChar(std::vector<TAlpha>& pattern) {
    std::unordered_map<TAlpha, std::vector<int> > badChar;
    for (size_t i = 0; i < pattern.size(); ++i) {
        badChar[pattern[i]].push_back(i);
    }
    return badChar;
}

std::vector<int> PreprocessNFunction(std::vector<TAlpha>& pattern) {
    std::vector<int> nFunction(pattern.size());
    // z-функция, запущенная справа налево
    for (int i = pattern.size() - 2, k = pattern.size() - 1; i >= 0; --i) {
        int l = k - nFunction[k] + 1;
        if (i >= l) {
            nFunction[i] = std::min(nFunction[pattern.size() - k + i - 1], i - l + 1);
        }
        
        while (i - nFunction[i] >= 0 && pattern[i - nFunction[i]] == pattern[pattern.size() - nFunction[i] - 1]) {
            nFunction[i]++;
        }
        
        if (i - nFunction[i] < l) {
            k = i;
        }
    }
    return nFunction;
}

struct TLFuntions {
    std::vector<int> l;
    std::vector<int> L;
};

TLFuntions PreprocessLFuntions(std::vector<TAlpha>& pattern, std::vector<int>& nFunction) {
    TLFuntions functions;
    functions.L.resize(pattern.size(),0);
    functions.l.resize(pattern.size() + 1, 0);

    for (int i = 0; i < static_cast<int>(pattern.size()); ++i) {
        if (nFunction[i] != 0) {
            int j = pattern.size() - nFunction[i];
            functions.L[j] = i;
        }

        int j = pattern.size() - i - 1;
        if (nFunction[i] == i + 1) {
            functions.l[j] = i + 1;
        }
        else {
            functions.l[j] = functions.l[j + 1];                        
        }
    }
    return functions;
}

int GetShiftBadChar(std::unordered_map<TAlpha, std::vector<int> >& badChar, std::vector<TAlpha>& text, int i, int j) {
    auto mapEl = badChar.find(text[i]);
    // Если знака нет в паттерне
    if (mapEl == badChar.end()) {
        return j + 1; // Двигаем паттерн за текущий элемент
    }

    auto begin = mapEl->second.begin();
    auto end = mapEl->second.end();
    
    auto it = std::lower_bound(begin, end, j);
    if (it == end) {
        --it; // В массиве всегда есть минимум 1 элемент
    }
    else if (*it >= j && it != begin) {
        --it; // Если есть куда двигаться
    }
    else {
        return j + 1; // Нет элемента в левой части паттерна => двигаем паттерн за текущий элемент
    }

    return j - *it; // Двигаем паттерн так, что бы на этом же месте остался такой же знак
}

int GetShiftGoodSuffix(TLFuntions& functions, std::vector<TAlpha>& pattern, int i, int j) {
    int shift = 0;
    if (j + 1 < static_cast<int>(pattern.size())) {
        if (functions.L[j + 1] > 0) {
            shift = pattern.size() - functions.L[j + 1] - 1;
        }
        else {
            shift = pattern.size() - functions.l[j + 1];
        }
    }
    return shift;
}

// Находит вхождения pattern в потоке text и возвращает пары вхождений (строка, слово)
std::vector<std::pair<int, int> > FindApoGian(std::vector<TAlpha>& pattern, std::istream& input) {
    std::vector<TAlpha> text;           // Текст
    std::vector<int> linesNumber;       // Массив окончаний строк linesNumber[i] = номер слова, на котором начинается i ая строка

    // Считываем текст
    ReadText(input, text, linesNumber);
    std::vector<int> mFunction(text.size());

    // Препроцессоринг паттерна
    std::unordered_map<TAlpha, std::vector<int> > badChar = PreprocessBadChar(pattern);
    std::vector<int> nFunction = PreprocessNFunction(pattern);
    TLFuntions lFunctions = PreprocessLFuntions(pattern, nFunction);

    // Фаза поиска
    std::vector<std::pair<int, int> > entries;
    if (pattern.size() == 0 || text.size() == 0) {
        return entries;
    }

    int currLine = 0;
    int k = static_cast<int>(pattern.size()) - 1;
    while (k < static_cast<int>(text.size())) {
        int j = static_cast<int>(pattern.size()) - 1;
        int i = k;

        while (j >= 0) {
            if (mFunction[i] == 0 || (mFunction[i] == nFunction[j] && nFunction[j] == 0)) {
                if (text[i] == pattern[j]) {
                    if (j == 0) {
                        mFunction[k] = pattern.size();
                        j = -1;
                        break;
                    }
                    else {
                        --i;
                        --j;
                    }
                }
                else {
                    mFunction[k] = k - i;
                    break;
                }
            }
            else if (mFunction[i] < nFunction[j]) {
                j -= mFunction[i];
                i -= mFunction[i];
            }
            else if (mFunction[i] >= nFunction[j] && nFunction[j] == j + 1) {
                mFunction[k] = k - i;
                j = -1;
                break;
            }
            else if (mFunction[i] > nFunction[j] && nFunction[j] < j + 1) {
                mFunction[k] = k - i;
                i -= nFunction[j];
                j -= nFunction[j];
                break;
            }
            else {
                j -= mFunction[i];
                i -= mFunction[i];
            }
        }
        if (j < 0) {
            while (linesNumber[currLine] <= k - static_cast<int>(pattern.size()) + 1) {
                ++currLine;
            }
            int word = k - static_cast<int>(pattern.size()) - linesNumber[currLine-1] + 2;
            entries.push_back(std::make_pair(currLine, word));
            k += pattern.size() - lFunctions.l[1]; // Переходим к следующему слову
        }
        else {
            int shift = 1;
            // Проверяем правило плохого символа
            shift = std::max(shift, GetShiftBadChar(badChar, text, i, j));
            // Проверяем правило хорошего суффикса
            shift = std::max(shift, GetShiftGoodSuffix(lFunctions, pattern, i, j));

            k += shift;
        }
    }

    return entries;
}