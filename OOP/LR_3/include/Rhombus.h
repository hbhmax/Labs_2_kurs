#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"

class Rhombus : public Figure {
private:
    double x, y;
    double diagonal1, diagonal2;

public:
    Rhombus();
    Rhombus(double x, double y, double d1, double d2);
    
    double area() const override;
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};

#endif