#include "../include/Pentagon.h"
#include <iostream>
#include <cmath>

#define M_PI 3.14159265

Pentagon::Pentagon() : x(0), y(0), radius(1) {}
Pentagon::Pentagon(double x, double y, double r) : x(x), y(y), radius(r) {}

double Pentagon::area() const {
    return (5.0 * radius * radius * std::sin(2.0 * M_PI / 5.0)) / 2.0;
}

std::pair<double, double> Pentagon::center() const {
    return {x, y};
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon vertices: ";
    for (int i = 0; i < 5; ++i) {
        double angle = 2.0 * M_PI * i / 5.0;
        double vx = x + radius * std::cos(angle);
        double vy = y + radius * std::sin(angle);
        os << "(" << vx << ", " << vy << ") ";
    }
}

void Pentagon::read(std::istream& is) {
    is >> x >> y >> radius;
}