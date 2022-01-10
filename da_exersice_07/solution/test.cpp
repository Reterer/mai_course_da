#include "solution.hpp"
#include "stdio.h"
#define LOG_T log(__func__, true)
#define LOG_F log(__func__, false)
#define TEST(a, b) (a == b) ? LOG_T : LOG_F

void log(const char* str, bool status) {
    fprintf(stderr, (status ? "[TRUE]\t%s\n" : "[FALSE]\t%s\n"), str);
    if(!status)
        exit(-1);
}

void test01() {
    TMatrix matrix = {
        {'0','1','0','1','1'},
        {'1','0','0','0','1'},
        {'0','1','0','0','0'},
        {'1','1','0','1','1'},
    };
    int ans = 4;

    TEST(TSolution::FindLargestArea(matrix), ans);
}

void test02() {
    TMatrix matrix = {
        {'1'}
    };
    int ans = 0;

    TEST(TSolution::FindLargestArea(matrix), ans);
}

void test03() {
    TMatrix matrix = {
        {'0'}
    };
    int ans = 1;

    TEST(TSolution::FindLargestArea(matrix), ans);
}

void test04() {
    TMatrix matrix = {
        {'0','0','1','1','1'},
        {'0','0','0','0','0'},
        {'0','0','0','0','0'},
        {'0','0','0','1','1'},
    };
    int ans = 10;

    TEST(TSolution::FindLargestArea(matrix), ans);
}

void test05() {
    TMatrix matrix = {
        {'0','0','0','1'},
        {'0','0','0','0'},
    };
    int ans = 6;

    TEST(TSolution::FindLargestArea(matrix), ans);
}

void test06() {
    TMatrix matrix = {
        {'1','1','0','0','0'},
        {'0','0','0','0','0'},
        {'0','0','0','0','0'},
        {'0','0','0','1','1'},
    };
    int ans = 10;

    TEST(TSolution::FindLargestArea(matrix), ans);
}

int main() {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
}