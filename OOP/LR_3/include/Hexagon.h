#ifndef HEXAGON_H
#define HEXAGON_H

#include "Figure.h"

class Hexagon : public Figure {
private:
    double x, y;
    double radius;

public:
    Hexagon();
    Hexagon(double x, double y, double r);
    
    double area() const override;
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};

#endif