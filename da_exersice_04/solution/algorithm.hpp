#pragma once
#include <vector>
#include <iostream>
#include "common.hpp"

// Находит вхождения pattern в потоке text и возвращает пары вхождений (строка, слово)
std::vector<std::pair<int, int> > FindApoGian(std::vector<TAlpha>& pattern, std::istream& input);