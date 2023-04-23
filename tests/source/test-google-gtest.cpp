#include <gtest/gtest.h>

// The function we want to test
int add(int a, int b) {
    return a + b;
}

// A basic test case
TEST(AddTest, PositiveNumbers) {
    EXPECT_EQ(add(2, 2), 4);
    EXPECT_EQ(add(0, 0), 0);
}

// Run the tests
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
