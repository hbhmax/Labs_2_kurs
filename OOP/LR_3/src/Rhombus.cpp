#include "../include/Rhombus.h"
#include <iostream>

Rhombus::Rhombus() : x(0), y(0), diagonal1(1), diagonal2(1) {}
Rhombus::Rhombus(double x, double y, double d1, double d2) : x(x), y(y), diagonal1(d1), diagonal2(d2) {}

double Rhombus::area() const {
    return (diagonal1 * diagonal2) / 2.0;
}

std::pair<double, double> Rhombus::center() const {
    return {x, y};
}

void Rhombus::print(std::ostream& os) const {
    double half_d1 = diagonal1 / 2.0;
    double half_d2 = diagonal2 / 2.0;
    
    os << "Rhombus vertices: ";
    os << "(" << x << ", " << y + half_d2 << ") ";
    os << "(" << x + half_d1 << ", " << y << ") ";
    os << "(" << x << ", " << y - half_d2 << ") ";
    os << "(" << x - half_d1 << ", " << y << ")";
}

void Rhombus::read(std::istream& is) {
    is >> x >> y >> diagonal1 >> diagonal2;
}