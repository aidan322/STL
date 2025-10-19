#include <gtest/gtest.h>
#include "CircularList.h"

TEST(CircularListTest, PushBackAndFront) {
    CircularList<int> list;
    EXPECT_TRUE(list.empty());

    list.push_back(10);
    list.push_back(20);

    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 20);
    EXPECT_EQ(list.size(), 2);
}

TEST(CircularListTest, PopFront) {
    CircularList<int> list;
    list.push_back(5);
    list.push_back(15);

    list.pop_front();
    EXPECT_EQ(list.front(), 15);
    EXPECT_EQ(list.size(), 1);
}

TEST(CircularListTest, IteratorTraversal) {
    CircularList<int> list;
    for (int i = 1; i <= 3; ++i)
        list.push_back(i);

    std::vector<int> values;
    for (auto it = list.begin(); it != list.end(); ++it)
        values.push_back(*it);

    EXPECT_EQ(values, (std::vector<int>{1, 2, 3}));
}

TEST(CircularListTest, OutputOperator) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::ostringstream oss;
    oss << list;
    EXPECT_EQ(oss.str(), "[1, 2, 3]");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
