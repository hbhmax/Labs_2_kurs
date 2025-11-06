#include "../include/Pentagon.h"
#include <iostream>
#include <cmath>

Pentagon::Pentagon() {
    x = 0;
    y = 0;
    radius = 1;
}

Pentagon::Pentagon(double x_val, double y_val, double r) {
    x = x_val;
    y = y_val;
    radius = r;
}

double Pentagon::area() const {
    return (5.0 * radius * radius * sin(2.0 * 3.14159 / 5.0)) / 2.0;
}

std::pair<double, double> Pentagon::center() const {
    return std::make_pair(x, y);
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon: ";
    for (int i = 0; i < 5; i++) {
        double angle = 2.0 * 3.14159 * i / 5.0;
        double vx = x + radius * cos(angle);
        double vy = y + radius * sin(angle);
        os << "(" << vx << ", " << vy << ") ";
    }
}

void Pentagon::read(std::istream& is) {
    is >> x >> y >> radius;
}