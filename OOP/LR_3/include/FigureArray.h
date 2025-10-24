#ifndef FIGUREARRAY_H
#define FIGUREARRAY_H

#include "Figure.h"
#include <memory>
#include <vector>

class FigureArray {
private:
    std::vector<std::unique_ptr<Figure>> figures;

public:
    void addFigure(std::unique_ptr<Figure> fig);
    void removeFigure(int index);
    double totalArea() const;
    void printAll() const;
    size_t size() const;
};

std::unique_ptr<Figure> createFigure(const std::string& type);

#endif