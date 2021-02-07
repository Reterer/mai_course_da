#include <gtest/gtest.h>

#include <string>
#include "../solution/rbtree.hpp"

TEST(rbtree, InitDeinit) {
    TRedBlackTree<std::string, uint64_t> tr;
}

TEST(rbtree, SimpleInsertAndSearch) {
    TRedBlackTree<uint64_t, std::string> tr;

    bool isInsert = tr.Insert(5, "five");
    bool isErrInsert = tr.Insert(5, "five");
    std::string *str = tr.Search(5);
    std::string *nullstr = tr.Search(42);
    
    ASSERT_EQ(isInsert, true);
    ASSERT_EQ(isErrInsert, false);
    ASSERT_EQ(*str, "five");
    ASSERT_EQ(nullstr, nullptr);
}

TEST(rbtree, InsertAndSearch) {
    TRedBlackTree<int, int> tr;
    
    for(int i = 0; i < 128; ++i)
        EXPECT_TRUE(tr.Insert(i, i)) << "I can't insert " << i << "element";
    for(int i = 0; i < 128; ++i)
        EXPECT_TRUE(tr.Search(i) != nullptr && *tr.Search(i) == i) << "I can't find " << i << " element";
}

TEST(rbtree, SimpleDelete) {
    TRedBlackTree<int, std::string> tr;

    tr.Insert(5, "five");
    bool isRemove = tr.Remove(5);
    bool isERRRemove = tr.Remove(5);

    ASSERT_EQ(isRemove, true);
    ASSERT_EQ(isERRRemove, false);
}

TEST(rbtree, Delete) {
    TRedBlackTree<int, int> tr;

    for(int i = 0; i < 16; ++i)
        tr.Insert(i, i);
    for(int i = 0; i < 16; ++i){
        EXPECT_TRUE(tr.Remove(i)) << "I can't remove";
    }
}