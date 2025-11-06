#include <gtest/gtest.h>
#include "../include/Figure.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include "../include/FigureArray.h"
#include <sstream>
#include <cmath>

TEST(RhombusTest, AreaCalculation) {
    Rhombus rhombus(0, 0, 4, 6);
    ASSERT_DOUBLE_EQ(rhombus.area(), 12.0);
}

TEST(RhombusTest, CenterCalculation) {
    Rhombus rhombus(2, 3, 4, 6);
    auto center = rhombus.center();
    ASSERT_DOUBLE_EQ(center.first, 2.0);
    ASSERT_DOUBLE_EQ(center.second, 3.0);
}

TEST(RhombusTest, InputOutput) {
    Rhombus rhombus;
    std::istringstream iss("1.0 2.0 3.0 4.0");
    iss >> rhombus;
    
    auto center = rhombus.center();
    ASSERT_DOUBLE_EQ(center.first, 1.0);
    ASSERT_DOUBLE_EQ(center.second, 2.0);
    ASSERT_DOUBLE_EQ(rhombus.area(), 6.0);
}

TEST(PentagonTest, AreaCalculation) {
    Pentagon pentagon(0, 0, 1);
    double area = pentagon.area();
    ASSERT_GT(area, 0);
}

TEST(PentagonTest, CenterCalculation) {
    Pentagon pentagon(5, 5, 2);
    auto center = pentagon.center();
    ASSERT_DOUBLE_EQ(center.first, 5.0);
    ASSERT_DOUBLE_EQ(center.second, 5.0);
}

TEST(HexagonTest, AreaCalculation) {
    Hexagon hexagon(0, 0, 1);
    double area = hexagon.area();
    double expectedArea = (3.0 * std::sqrt(3.0) * 1 * 1) / 2.0;
    ASSERT_NEAR(area, expectedArea, 0.0001);
}

TEST(HexagonTest, CenterCalculation) {
    Hexagon hexagon(3, 4, 2);
    auto center = hexagon.center();
    ASSERT_DOUBLE_EQ(center.first, 3.0);
    ASSERT_DOUBLE_EQ(center.second, 4.0);
}

TEST(FigureArrayTest, AddAndTotalArea) {
    FigureArray array;
    
    array.addFigure(std::make_unique<Rhombus>(0, 0, 2, 3));
    array.addFigure(std::make_unique<Pentagon>(0, 0, 1));
    
    ASSERT_GT(array.totalArea(), 0);
    ASSERT_EQ(array.size(), 2);
}

TEST(FigureArrayTest, RemoveFigure) {
    FigureArray array;
    
    array.addFigure(std::make_unique<Rhombus>(0, 0, 2, 3));
    array.addFigure(std::make_unique<Pentagon>(0, 0, 1));
    
    ASSERT_EQ(array.size(), 2);
    array.removeFigure(0);
    ASSERT_EQ(array.size(), 1);
}

TEST(FigureArrayTest, EmptyArray) {
    FigureArray array;
    ASSERT_DOUBLE_EQ(array.totalArea(), 0.0);
    ASSERT_EQ(array.size(), 0);
}

TEST(FactoryTest, CreateFigures) {
    auto rhombus = createFigure("rhombus");
    ASSERT_NE(rhombus, nullptr);
    
    auto pentagon = createFigure("pentagon");
    ASSERT_NE(pentagon, nullptr);
    
    auto hexagon = createFigure("hexagon");
    ASSERT_NE(hexagon, nullptr);
    
    auto invalid = createFigure("invalid");
    ASSERT_EQ(invalid, nullptr);
}

TEST(OperatorTest, DoubleConversion) {
    Rhombus rhombus(0, 0, 4, 6);
    double area = static_cast<double>(rhombus);
    ASSERT_DOUBLE_EQ(area, 12.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}