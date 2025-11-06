#include "../include/Hexagon.h"
#include <iostream>
#include <cmath>

Hexagon::Hexagon() {
    x = 0;
    y = 0;
    radius = 1;
}

Hexagon::Hexagon(double x_val, double y_val, double r) {
    x = x_val;
    y = y_val;
    radius = r;
}

double Hexagon::area() const {
    return (3.0 * sqrt(3.0) * radius * radius) / 2.0;
}

std::pair<double, double> Hexagon::center() const {
    return std::make_pair(x, y);
}

void Hexagon::print(std::ostream& os) const {
    os << "Hexagon: ";
    for (int i = 0; i < 6; i++) {
        double angle = 2.0 * 3.14159 * i / 6.0;
        double vx = x + radius * cos(angle);
        double vy = y + radius * sin(angle);
        os << "(" << vx << ", " << vy << ") ";
    }
}

void Hexagon::read(std::istream& is) {
    is >> x >> y >> radius;
}