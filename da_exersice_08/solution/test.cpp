#include "solution.hpp"
#include <stdio.h>
#include <vector>

#define LOG_T log(__func__, true)
#define LOG_F log(__func__, false)
#define TEST(a) (a) ? LOG_T : LOG_F;

void log(const char* str, bool status) {
    fprintf(stderr, (status ? "[TRUE]\t%s\n" : "[FALSE]\t%s\n"), str);
    if(!status)
        exit(-1);
}

bool operator==(TSegment& a, TSegment& b){
    return a.left == b.left && a.right == b.right;
}

void test01() {
    int m = 0;
    std::vector<TSegment> list = {};
    std::vector<TSegment> trueAns = {};

    auto ans = Solution(list, m);
    TEST(ans.size() == trueAns.size() && std::equal(trueAns.begin(), trueAns.end(), ans.begin()));
}

void test02() {
    int m = 1;
    std::vector<TSegment> list = {
        {-1, 0, 0},
        {-5, -3, 1},
        {2, 5, 2},
    };
    std::vector<TSegment> trueAns = {};

    auto ans = Solution(list, m);
    TEST(ans.size() == trueAns.size() && std::equal(trueAns.begin(), trueAns.end(), ans.begin()));
}

void test03() {
    int m = 7;
    std::vector<TSegment> list = {
        {-3, 1, 0},
        {0, 3, 1},
        {2, 4, 2},
        {2, 5, 3},
        {5, 10, 4},

    };
    std::vector<TSegment> trueAns = {
        {0, 3, 1},
        {2, 5, 3},
        {5, 10, 4},
    };

    auto ans = Solution(list, m);
    TEST(ans.size() == trueAns.size() && std::equal(trueAns.begin(), trueAns.end(), ans.begin()));
}

void test04() {
    int m = 7;
    std::vector<TSegment> list = {
        {-3, 1, 0},
        {0, 3, 1},
        {2, 4, 2},
        {5, 7, 3},
        {5, 10, 4},

    };
    std::vector<TSegment> trueAns = {
    };

    auto ans = Solution(list, m);
    TEST(ans.size() == trueAns.size() && std::equal(trueAns.begin(), trueAns.end(), ans.begin()));
}

int main() {
    test01();
    test02();
    test03();
    test04();
}