#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <utility>

class Figure {
public:
    virtual ~Figure() = default;
    
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual std::pair<double, double> center() const = 0;
    
    explicit operator double() const { return area(); }
};

std::ostream& operator<<(std::ostream& os, const Figure& fig);
std::istream& operator>>(std::istream& is, Figure& fig);

#endif