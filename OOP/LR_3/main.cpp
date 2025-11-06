#include "include/FigureArray.h"
#include <iostream>
#include <sstream>
#include <memory>

int main() {
    FigureArray figures;
    std::string line;
    
    std::cout << "Enter figures (rhombus/pentagon/hexagon with parameters):" << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  rhombus 0 0 4 6" << std::endl;
    std::cout << "  pentagon 1 1 5" << std::endl;
    std::cout << "  hexagon 2 2 3" << std::endl;
    std::cout << "Type 'exit' to finish" << std::endl;
    
    while (std::getline(std::cin, line)) {
        if (line == "exit") break;
        
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        
        auto fig = createFigure(type);
        if (fig != nullptr) {
            iss >> *fig;
            figures.addFigure(std::move(fig));
            std::cout << "Figure added!" << std::endl;
        } else {
            std::cout << "Unknown figure: " << type << std::endl;
        }
    }
    
    std::cout << std::endl << "=== All Figures ===" << std::endl;
    figures.printAll();
    
    std::cout << "Total area: " << figures.totalArea() << std::endl;
    
    if (figures.size() > 0) {
        std::cout << std::endl << "Enter index to remove (0-" << figures.size()-1 << "): ";
        int index;
        std::cin >> index;
        figures.removeFigure(index);
        
        std::cout << "=== After removal ===" << std::endl;
        figures.printAll();
        std::cout << "Total area: " << figures.totalArea() << std::endl;
    }
    
    return 0;
}