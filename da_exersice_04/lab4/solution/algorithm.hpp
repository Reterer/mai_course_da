#pragma once
#include <vector>
#include "common.hpp"

class TSubstringFinder {
public:
    TSubstringFinder(std::vector<TAlpha>& pattern, std::istream& textStream);
    // Находит вхождения pattern в потоке text и выводит их
    void Find();

private:
    // Препроцессоринг, Правило плохого символа
    void PreprocessBadChar();
    // Препроцессоринг, Правило хорошего суффикса
    void PreprocessGoodSuffix();
    // Считывание текста из потока
    void ReadText();
    // Получения свдига от правила плохого символа
    // i - индекс в тексте
    // j - индекс в паттерне
    int GetShiftBadChar(int i, int j);
    // Получения свдига от правила хорошего суффикса
    // i - индекс в тексте
    // j - индекс в паттерне
    int GetShiftGoodSuffix(int i, int j);
    // Пропуск сравнения Апостолико-Джанкарло
    void SkipElements(int k, int& i, int& j);

private:
    std::vector<TAlpha>& pattern;       // Паттерн
    std::vector<TAlpha> text;           // Текст
    std::vector<int> linesNumber;       // Массив окончаний строк linesNumber[i] = номер слова, на котором начинается i ая строка
    std::istream& textStream;           // Поток, из которого считывается текст

    std::map<TAlpha, std::vector<int> > badChar; // Структура, хранящая смещения для ППС
    std::vector<int> LFunction;                  // Структура, хранящая смещения для ПХС
    std::vector<int> lFunction;                  // Структура, хранящая смещения для ПХС
    std::vector<int> nFunction;                  // Структура, реверснутая зет-функция
    std::vector<int> mFunction;                  // Структура, хранящая длину подстроки текста, которая точно совпадет с суффиксом паттерна
};