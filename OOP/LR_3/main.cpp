#include "../include/FigureArray.h"
#include <iostream>
#include <sstream>

int main() {
    FigureArray figures;
    std::string line;
    
    std::cout << "Enter figures (type: rhombus/pentagon/hexagon followed by parameters):" << std::endl;
    std::cout << "Format examples:" << std::endl;
    std::cout << "  rhombus x y diagonal1 diagonal2" << std::endl;
    std::cout << "  pentagon x y radius" << std::endl;
    std::cout << "  hexagon x y radius" << std::endl;
    std::cout << "Enter 'exit' to finish input" << std::endl;
    
    while (std::getline(std::cin, line)) {
        if (line == "exit") break;
        
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        
        auto fig = createFigure(type);
        if (fig) {
            iss >> *fig;
            figures.addFigure(std::move(fig));
            std::cout << "Figure added successfully!" << std::endl;
        } else {
            std::cout << "Unknown figure type: " << type << std::endl;
        }
    }
    
    std::cout << "\n=== All Figures ===" << std::endl;
    figures.printAll();
    
    std::cout << "\nTotal area of all figures: " << figures.totalArea() << std::endl;
    
    if (figures.size() > 0) {
        std::cout << "\nEnter index to remove (0-" << figures.size()-1 << "): ";
        int index;
        std::cin >> index;
        figures.removeFigure(index);
        
        std::cout << "\n=== After Removal ===" << std::endl;
        figures.printAll();
        std::cout << "Total area: " << figures.totalArea() << std::endl;
    }
    
    return 0;
}