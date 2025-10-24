#include <iostream>
#include <memory>
#include "include/Array.h"
#include "include/Rectangle.h"
#include "include/Trapezoid.h"
#include "include/Rhombus.h"

using namespace std;

int main() {
    Array<shared_ptr<Figure<int>>> figures;
    
    cout << "Добавляем фигуры в массив:" << endl;
    
    // Прямоугольник
    auto rect = make_shared<Rectangle<int>>(0, 0, 5, 3);
    figures.push_back(rect);
    cout << "Добавлен прямоугольник" << endl;
    
    // Трапеция
    auto trap = make_shared<Trapezoid<int>>(0, 0, 3, 6, 4);
    figures.push_back(trap);
    cout << "Добавлена трапеция" << endl;
    
    // Ромб
    auto rhomb = make_shared<Rhombus<int>>(0, 0, 6, 8);
    figures.push_back(rhomb);
    cout << "Добавлен ромб" << endl;
    
    cout << "\n=== Информация о всех фигурах ===" << endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << "Фигура " << i << ": ";
        figures[i]->print();
        Point<int> center = figures[i]->center();
        cout << "  Центр: (" << center.getX() << ", " << center.getY() << ")" << endl;
        cout << "  Площадь: " << figures[i]->area() << endl << endl;
    }
    
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += figures[i]->area();
    }
    cout << "Общая площадь всех фигур: " << total_area << endl;
    
    cout << "\n=== Удаление фигуры с индексом 1 ===" << endl;
    figures.erase(1);
    
    cout << "Фигуры после удаления:" << endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << "Фигура " << i << ": ";
        figures[i]->print();
    }
    
    cout << "\n=== Демонстрация работы с Array<Rectangle<int>> ===" << endl;
    Array<shared_ptr<Rectangle<int>>> rectangles;
    rectangles.push_back(make_shared<Rectangle<int>>(1, 1, 4, 2));
    rectangles.push_back(make_shared<Rectangle<int>>(2, 2, 3, 3));
    
    for (size_t i = 0; i < rectangles.size(); ++i) {
        cout << "Прямоугольник " << i << ": ";
        rectangles[i]->print();
    }
    
    return 0;
}