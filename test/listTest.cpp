#include <gtest/gtest.h>
#include "List.h"

class ListTest : public testing::Test {
public:
    List<int> *l;
    int size = 0;

    void SetUp() {}
    void TearDown() {}
};

TEST_F(ListTest, InitList) {
    l = new List<int>;
    ASSERT_TRUE(!l->getHead());
    ASSERT_TRUE(!l->getTail());
}

TEST_F(ListTest, FillList) {
    for (int i = 0; i < 50; ++i) {
        l->pushToTail(i);
        ++size;
    }
    EXPECT_EQ(l->getValue(getHead()), 0);
    EXPECT_EQ(l->getValue(getTail()), 49);
    ASSERT_EQ(size, 50);
}

TEST_F(ListTest, ClearList) {
    l->clear();
    size = 0;
    ASSERT_EQ(l->isEmpty(), true);
}

TEST_F(ListTest, PushAndPop) {
    l->pushToTail(size++);
    int popped = l->pop(getTail());
    size = 0;

    ASSERT_EQ(popped, 0);
    ASSERT_EQ(l->pop(getTail()), INT32_MIN);
}

TEST_F(ListTest, SortList) {
    l->clear();
    for (int i = 4; i >= 0; --i)
        l->pushToTail(i);
    l->sort();

    for (int i = 0; i < 5; ++i)
        ASSERT_EQ(l->pop(getHead()), i);
}
