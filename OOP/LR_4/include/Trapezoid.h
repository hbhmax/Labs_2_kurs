#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"

template<typename T>
class Trapezoid : public Figure<T> {
private:
    T top_base;
    T bottom_base;
    T height;
    
public:
    Trapezoid(T center_x, T center_y, T top_base, T bottom_base, T height) {
        this->top_base = top_base;
        this->bottom_base = bottom_base;
        this->height = height;
        
        T top_offset = top_base / 2;
        T bottom_offset = bottom_base / 2;
        
        this->addPoint(center_x - bottom_offset, center_y - height/2);
        this->addPoint(center_x + bottom_offset, center_y - height/2);
        this->addPoint(center_x + top_offset, center_y + height/2);
        this->addPoint(center_x - top_offset, center_y + height/2);
    }
    
    double area() const override {
        return (top_base + bottom_base) * height / 2.0;
    }
    
    void print() const override {
        std::cout << "Трапеция: ";
        for (const auto& point : this->points) {
            std::cout << "(" << point->getX() << ", " << point->getY() << ") ";
        }
        std::cout << std::endl;
    }
    
    Point<T> center() const override {
        T x_center = 0;
        T y_center = 0;
        for (const auto& point : this->points) {
            x_center += point->getX();
            y_center += point->getY();
        }
        return Point<T>(x_center / this->points.size(), y_center / this->points.size());
    }
};

#endif