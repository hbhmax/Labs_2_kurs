#include <gtest/gtest.h>
#include <memory>
#include "../include/Point.h"
#include "../include/Figure.h"
#include "../include/Rectangle.h"
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Array.h"

using namespace std;

TEST(PointTest, BasicCreation) {
    Point<int> p(3, 4);
    EXPECT_EQ(p.getX(), 3);
    EXPECT_EQ(p.getY(), 4);
}

TEST(PointTest, Setters) {
    Point<int> p(0, 0);
    p.setX(5);
    p.setY(6);
    EXPECT_EQ(p.getX(), 5);
    EXPECT_EQ(p.getY(), 6);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle<int> rect(0, 0, 4, 3);
    EXPECT_DOUBLE_EQ(rect.area(), 12.0);
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle<int> rect(0, 0, 4, 2);
    Point<int> center = rect.center();
    EXPECT_EQ(center.getX(), 2);
    EXPECT_EQ(center.getY(), 1);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid<int> trap(0, 0, 3, 5, 4);
    EXPECT_DOUBLE_EQ(trap.area(), 16.0);
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid<int> trap(0, 0, 2, 4, 4);
    Point<int> center = trap.center();
    EXPECT_EQ(center.getX(), 0);
    EXPECT_EQ(center.getY(), 0);
}

TEST(RhombusTest, AreaCalculation) {
    Rhombus<int> rhomb(0, 0, 6, 8);
    EXPECT_DOUBLE_EQ(rhomb.area(), 24.0);
}

TEST(RhombusTest, CenterCalculation) {
    Rhombus<int> rhomb(0, 0, 6, 8);
    Point<int> center = rhomb.center();
    EXPECT_EQ(center.getX(), 0);
    EXPECT_EQ(center.getY(), 0);
}

TEST(ArrayTest, BasicOperations) {
    Array<shared_ptr<Figure<int>>> figures;
    
    EXPECT_EQ(figures.size(), 0);
    
    figures.push_back(make_shared<Rectangle<int>>(0, 0, 4, 3));
    EXPECT_EQ(figures.size(), 1);
    
    figures.push_back(make_shared<Trapezoid<int>>(0, 0, 3, 5, 4));
    EXPECT_EQ(figures.size(), 2);
    
    figures.erase(0);
    EXPECT_EQ(figures.size(), 1);
}

TEST(ArrayTest, ElementAccess) {
    Array<shared_ptr<Figure<int>>> figures;
    auto rect = make_shared<Rectangle<int>>(0, 0, 4, 3);
    figures.push_back(rect);
    
    EXPECT_DOUBLE_EQ(figures[0]->area(), 12.0);
}

TEST(ArrayTest, TotalAreaCalculation) {
    Array<shared_ptr<Figure<int>>> figures;
    figures.push_back(make_shared<Rectangle<int>>(0, 0, 4, 3));
    figures.push_back(make_shared<Trapezoid<int>>(0, 0, 3, 5, 4));
    figures.push_back(make_shared<Rhombus<int>>(0, 0, 6, 8));
    
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += figures[i]->area();
    }
    
    EXPECT_DOUBLE_EQ(total_area, 52.0);
}

TEST(TemplateTest, DifferentTypes) {
    Rectangle<double> rect_double(0.5, 1.5, 2.5, 3.5);
    EXPECT_DOUBLE_EQ(rect_double.area(), 8.75);
    
    Rectangle<float> rect_float(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(rect_float.area(), 12.0f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}