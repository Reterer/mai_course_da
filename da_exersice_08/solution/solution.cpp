#include "solution.hpp"

std::vector<TSegment> Solution(const std::vector<TSegment>& list, int m) {
    std::vector<TSegment> sortedList(list.begin(), list.end());
    int n = sortedList.size();

    std::sort(sortedList.begin(), sortedList.end(), [](TSegment& lhs, TSegment& rhs){
        if(lhs.left < rhs.left)
            return true;
        return lhs.left == rhs.left && lhs.right < rhs.right;
    });

    std::vector<TSegment> selectedSegments;
    
    int currRight = 0; // правый конец текущего отрезка
    int maxRight = -1; // правый конец отрезка, который мы хотим выбрать
    int maxIdx = -1;

    bool isCorrect = false;

    for(int i = 0; i < n; ++i) {
        if(sortedList[i].left <= currRight && maxRight < sortedList[i].right) {
            maxRight = sortedList[i].right;
            maxIdx = i;
        }Ё
        else if(sortedList[i].left > currRight) {
            if(maxIdx == -1) {
                maxIdx = -1;
                break;
            }
            // Добавляем новый отрезок
            selectedSegments.push_back(sortedList[maxIdx]);
            currRight = maxRight;

            // Проверяем, что мы достигли m
            if(sortedList[maxIdx].right >= m) {
                isCorrect = true;
                maxIdx = -1;
                break;
            }

            // Обрабатываем текущий отрезок
            if(sortedList[i].left <= currRight && maxRight < sortedList[i].right) {
                maxRight = sortedList[i].right;
                maxIdx = i;
            }
            // Если текущий отрезок не пересекается 
            else if(sortedList[i].left > currRight) {
                maxIdx = -1;
                break;
            }
        }
    }

    // Обрабатываем последний элемент
    if(maxIdx != -1) {
        if(sortedList[maxIdx].right >= m) {
            selectedSegments.push_back(sortedList[maxIdx]);
            isCorrect = true;
        }
    }

    if(isCorrect) {
        std::sort(selectedSegments.begin(), selectedSegments.end(), [](TSegment& lhs, TSegment& rhs){
            return lhs.i < rhs.i;
        });
        return selectedSegments;
    }
    return {};
}