#include <gtest/gtest.h>
#include "../include/removeVowels.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(removeVowels("This is good")=="Ths s gd");
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(removeVowels("1a2a3a4a")=="12");
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(removeVowels("MINIMUM")=="MNMM");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}