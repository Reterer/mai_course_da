#include "vector"
#include "iostream"

typedef std::vector<std::vector<char>> TMatrix;

/*
    TSolution - находит ответ на задачу.
    Используется следующим образом:
        TSolution::FindLargestArea(matrix)
*/

class TSolution {
public:
    TSolution();
    static int FindLargestArea(const TMatrix& matrix);
private:
    struct TRectInfo {
        int Height; // Высота прямоугольника
        int Start;  // Левая граница прямоугольника включительно
        int End;    // Правая граница прямоугольнка невключительно
    };
};

// Считывает и перезаписывает матрицу
void ReadMatrix(TMatrix& matrix);