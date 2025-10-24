#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"

template<typename T>
class Rectangle : public Figure<T> {
private:
    T width;
    T height;
    
public:
    Rectangle(T x1, T y1, T width, T height) {
        this->width = width;
        this->height = height;
        this->addPoint(x1, y1);
        this->addPoint(x1 + width, y1);
        this->addPoint(x1 + width, y1 + height);
        this->addPoint(x1, y1 + height);
    }
    
    double area() const override {
        return width * height;
    }
    
    void print() const override {
        std::cout << "Прямоугольник: ";
        for (const auto& point : this->points) {
            std::cout << "(" << point->getX() << ", " << point->getY() << ") ";
        }
        std::cout << std::endl;
    }
    
    Point<T> center() const override {
        return Point<T>((this->points[0]->getX() + this->points[2]->getX()) / 2,
                       (this->points[0]->getY() + this->points[2]->getY()) / 2);
    }
};

#endif
