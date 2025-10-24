#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"

class Pentagon : public Figure {
private:
    double x, y;
    double radius;

public:
    Pentagon();
    Pentagon(double x, double y, double r);
    
    double area() const override;
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};

#endif