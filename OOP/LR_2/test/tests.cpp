#include <gtest/gtest.h>
#include "../interfaces/Octal.h"
#include <stdexcept>

using namespace std;

TEST(OctalTest, DefaultConstructor) {
    Octal num;
    EXPECT_EQ(num.toString(), "0");
    EXPECT_EQ(num.getSize(), 1);
}

TEST(OctalTest, SizeValueConstructor) {
    Octal num(3, 5);
    EXPECT_EQ(num.toString(), "555");
    EXPECT_EQ(num.getSize(), 3);
}

TEST(OctalTest, InitializerListConstructor) {
    Octal num = {1, 2, 3};
    EXPECT_EQ(num.toString(), "123");
    EXPECT_EQ(num.getSize(), 3);
}

TEST(OctalTest, StringConstructor) {
    Octal num("456");
    EXPECT_EQ(num.toString(), "456");
    EXPECT_EQ(num.getSize(), 3);
}

TEST(OctalTest, CopyConstructor) {
    Octal num1("123");
    Octal num2(num1);
    EXPECT_EQ(num2.toString(), "123");
    EXPECT_TRUE(num1.equals(num2));
}

TEST(OctalTest, InvalidOctalDigit) {
    EXPECT_THROW(Octal(3, 8), invalid_argument);
    EXPECT_THROW(Octal({1, 8, 3}), invalid_argument);
    EXPECT_THROW(Octal("128"), invalid_argument);
}

TEST(OctalTest, Equals) {
    Octal num1("123");
    Octal num2("123");
    Octal num3("124");
    
    EXPECT_TRUE(num1.equals(num2));
    EXPECT_FALSE(num1.equals(num3));
}

TEST(OctalTest, LessThan) {
    Octal num1("123");
    Octal num2("124");
    Octal num3("122");
    
    EXPECT_TRUE(num1.lessThan(num2));
    EXPECT_FALSE(num1.lessThan(num3));
    EXPECT_FALSE(num1.lessThan(num1));
}

TEST(OctalTest, GreaterThan) {
    Octal num1("124");
    Octal num2("123");
    Octal num3("125");
    
    EXPECT_TRUE(num1.greaterThan(num2));
    EXPECT_FALSE(num1.greaterThan(num3));
    EXPECT_FALSE(num1.greaterThan(num1));
}

TEST(OctalTest, Add) {
    Octal num1("12");
    Octal num2("7");
    Octal result = num1.add(num2);
    
    EXPECT_EQ(result.toString(), "21");
}

TEST(OctalTest, AddWithCarry) {
    Octal num1("77");
    Octal num2("1");
    Octal result = num1.add(num2);
    
    EXPECT_EQ(result.toString(), "100");
}

TEST(OctalTest, Subtract) {
    Octal num1("21");
    Octal num2("7");
    Octal result = num1.subtract(num2);
    
    EXPECT_EQ(result.toString(), "12");
}

TEST(OctalTest, SubtractToZero) {
    Octal num1("10");
    Octal num2("10");
    Octal result = num1.subtract(num2);
    
    EXPECT_EQ(result.toString(), "0");
}

TEST(OctalTest, SubtractNegativeResult) {
    Octal num1("7");
    Octal num2("10");
    
    EXPECT_THROW(num1.subtract(num2), invalid_argument);
}

TEST(OctalTest, AddAssign) {
    Octal num1("12");
    Octal num2("7");
    num1.addAssign(num2);
    
    EXPECT_EQ(num1.toString(), "21");
}

TEST(OctalTest, SubtractAssign) {
    Octal num1("21");
    Octal num2("7");
    num1.subtractAssign(num2);
    
    EXPECT_EQ(num1.toString(), "12");
}

TEST(OctalTest, ZeroOperations) {
    Octal zero;
    Octal num("123");
    
    EXPECT_TRUE(zero.add(num).equals(num));
    EXPECT_TRUE(num.subtract(zero).equals(num));
    EXPECT_TRUE(zero.equals(zero.copy()));
}

TEST(OctalTest, LargeNumbers) {
    Octal num1("7777777");
    Octal num2("1");
    Octal result = num1.add(num2);
    
    EXPECT_EQ(result.toString(), "10000000");
}

TEST(OctalTest, GetDigit) {
    Octal num("123");
    
    EXPECT_EQ(num.getDigit(0), 3);
    EXPECT_EQ(num.getDigit(1), 2);
    EXPECT_EQ(num.getDigit(2), 1);
    
    EXPECT_THROW(num.getDigit(3), out_of_range);
}

TEST(OctalTest, CopyMethod) {
    Octal original("123");
    Octal copy = original.copy();
    
    EXPECT_TRUE(original.equals(copy));
    EXPECT_EQ(original.toString(), copy.toString());
}

TEST(OctalTest, MoveConstructor) {
    Octal original("123");
    Octal moved(move(original));
    
    EXPECT_EQ(moved.toString(), "123");
    EXPECT_GE(original.getSize(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}