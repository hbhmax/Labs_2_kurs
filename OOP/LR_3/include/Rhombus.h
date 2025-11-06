#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"

class Rhombus : public Figure {
public:
    double x, y;
    double d1, d2;
    
    Rhombus();
    Rhombus(double x_val, double y_val, double d1_val, double d2_val);
    
    double area() const override;
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
};

#endif