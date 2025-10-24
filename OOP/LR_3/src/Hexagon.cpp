#include "../include/Hexagon.h"
#include <iostream>
#include <cmath>

#define M_PI 3.14159265

Hexagon::Hexagon() : x(0), y(0), radius(1) {}
Hexagon::Hexagon(double x, double y, double r) : x(x), y(y), radius(r) {}

double Hexagon::area() const {
    return (3.0 * std::sqrt(3.0) * radius * radius) / 2.0;
}

std::pair<double, double> Hexagon::center() const {
    return {x, y};
}

void Hexagon::print(std::ostream& os) const {
    os << "Hexagon vertices: ";
    for (int i = 0; i < 6; ++i) {
        double angle = 2.0 * M_PI * i / 6.0;
        double vx = x + radius * std::cos(angle);
        double vy = y + radius * std::sin(angle);
        os << "(" << vx << ", " << vy << ") ";
    }
}

void Hexagon::read(std::istream& is) {
    is >> x >> y >> radius;
}