#include "../include/FigureArray.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include <iostream>
#include <memory>
#include <vector>
#include <cctype>

void FigureArray::addFigure(std::unique_ptr<Figure> fig) {
    figures.push_back(std::move(fig));
}

void FigureArray::removeFigure(int index) {
    if (index >= 0 && index < figures.size()) {
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
    for (size_t i = 0; i < figures.size(); i++) {
        std::cout << "Figure " << i << ": ";
        auto center = figures[i]->center();
        std::cout << *figures[i] << " | Center: (" << center.first << ", " << center.second << ")";
        std::cout << " | Area: " << figures[i]->area() << std::endl;
    }
}

int FigureArray::size() const {
    return figures.size();
}

std::unique_ptr<Figure> createFigure(const std::string& type) {
    std::string lowerType = type;
    for (int i = 0; i < lowerType.length(); i++) {
        lowerType[i] = tolower(lowerType[i]);
    }
    
    if (lowerType == "rhombus") return std::make_unique<Rhombus>();
    if (lowerType == "pentagon") return std::make_unique<Pentagon>();
    if (lowerType == "hexagon") return std::make_unique<Hexagon>();

    return nullptr;
}