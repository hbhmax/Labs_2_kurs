#include "../include/Rhombus.h"
#include <iostream>

Rhombus::Rhombus() {
    x = 0;
    y = 0;
    d1 = 1;
    d2 = 1;
}

Rhombus::Rhombus(double x_val, double y_val, double d1_val, double d2_val) {
    x = x_val;
    y = y_val;
    d1 = d1_val;
    d2 = d2_val;
}

double Rhombus::area() const {
    return (d1 * d2) / 2.0;
}

std::pair<double, double> Rhombus::center() const {
    return std::make_pair(x, y);
}

void Rhombus::print(std::ostream& os) const {
    double half_d1 = d1 / 2.0;
    double half_d2 = d2 / 2.0;
    
    os << "Rhombus: ";
    os << "(" << x << ", " << y + half_d2 << ") ";
    os << "(" << x + half_d1 << ", " << y << ") ";
    os << "(" << x << ", " << y - half_d2 << ") ";
    os << "(" << x - half_d1 << ", " << y << ")";
}

void Rhombus::read(std::istream& is) {
    is >> x >> y >> d1 >> d2;
}