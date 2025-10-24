#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"

template<typename T>
class Rhombus : public Figure<T> {
private:
    T diagonal1;
    T diagonal2;
    
public:
    Rhombus(T center_x, T center_y, T diagonal1, T diagonal2) {
        this->diagonal1 = diagonal1;
        this->diagonal2 = diagonal2;
        
        this->addPoint(center_x, center_y + diagonal2/2);
        this->addPoint(center_x + diagonal1/2, center_y);
        this->addPoint(center_x, center_y - diagonal2/2);
        this->addPoint(center_x - diagonal1/2, center_y);
    }
    
    double area() const override {
        return (diagonal1 * diagonal2) / 2.0;
    }
    
    void print() const override {
        std::cout << "Ромб: ";
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