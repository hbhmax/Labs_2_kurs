#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <vector>
#include <memory>

template<typename T>
class Figure {
protected:
    std::vector<std::unique_ptr<Point<T>>> points;
    
public:
    virtual ~Figure() = default;
    
    virtual double area() const = 0;
    virtual void print() const = 0;
    virtual Point<T> center() const = 0;
    
    void addPoint(T x, T y) {
        points.emplace_back(std::make_unique<Point<T>>(x, y));
    }
};

#endif
