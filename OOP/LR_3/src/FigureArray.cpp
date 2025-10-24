#include "../include/FigureArray.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include <iostream>
#include <algorithm>
#include <cctype>

void FigureArray::addFigure(std::unique_ptr<Figure> fig) {
    figures.push_back(std::move(fig));
}

void FigureArray::removeFigure(int index) {
    if (index >= 0 && index < static_cast<int>(figures.size())) {
        figures.erase(figures.begin() + index);
    }
}

double FigureArray::totalArea() const {
    double total = 0;
    for (const auto& fig : figures) {
        total += fig->area();
    }
    return total;
}

void FigureArray::printAll() const {
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i << ": ";
        auto center = figures[i]->center();
        std::cout << *figures[i] << " | Center: (" << center.first << ", " << center.second 
                  << ") | Area: " << figures[i]->area() << std::endl;
    }
}

size_t FigureArray::size() const {
    return figures.size();
}

std::unique_ptr<Figure> createFigure(const std::string& type) {
    std::string lowerType = type;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    if (lowerType == "rhombus") return std::unique_ptr<Rhombus>(new Rhombus());
    if (lowerType == "pentagon") return std::unique_ptr<Pentagon>(new Pentagon());
    if (lowerType == "hexagon") return std::unique_ptr<Hexagon>(new Hexagon());
    return nullptr;
}