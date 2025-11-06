#include <iostream>
#include <memory>
#include "include/Array.h"
#include "include/Rectangle.h"
#include "include/Trapezoid.h"
#include "include/Rhombus.h"

using namespace std;

int main() {
    Array<shared_ptr<Figure<int>>> figures;
    
    cout << "Adding figures to array:" << endl;
    
    auto rect = make_shared<Rectangle<int>>(0, 0, 5, 3);
    figures.push_back(rect);
    cout << "Added rectangle" << endl;
    
    auto trap = make_shared<Trapezoid<int>>(0, 0, 3, 6, 4);
    figures.push_back(trap);
    cout << "Added trapezoid" << endl;
    
    auto rhomb = make_shared<Rhombus<int>>(0, 0, 6, 8);
    figures.push_back(rhomb);
    cout << "Added rhombus" << endl;
    
    cout << "\n=== Information about all figures ===" << endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << "Figure " << i << ": ";
        figures[i]->print();
        Point<int> center = figures[i]->center();
        cout << "  Center: (" << center.getX() << ", " << center.getY() << ")" << endl;
        cout << "  Area: " << figures[i]->area() << endl << endl;
    }
    
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += figures[i]->area();
    }
    cout << "Total area of all figures: " << total_area << endl;
    
    cout << "\n=== Deleting figure at index 1 ===" << endl;
    figures.erase(1);
    
    cout << "Figures after deletion:" << endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << "Figure " << i << ": ";
        figures[i]->print();
    }
    
    cout << "\n=== Demonstration of Array<Rectangle<int>> work ===" << endl;
    Array<shared_ptr<Rectangle<int>>> rectangles;
    rectangles.push_back(make_shared<Rectangle<int>>(1, 1, 4, 2));
    rectangles.push_back(make_shared<Rectangle<int>>(2, 2, 3, 3));
    
    for (size_t i = 0; i < rectangles.size(); ++i) {
        cout << "Rectangle " << i << ": ";
        rectangles[i]->print();
    }
    
    return 0;
}