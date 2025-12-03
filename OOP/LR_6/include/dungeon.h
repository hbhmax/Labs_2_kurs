#pragma once
#include "npc.h"
#include "observer.h"
#include "visitor.h"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

class Dungeon {
public:
    // Добавление NPC в подземелье
    void addNPC(std::unique_ptr<NPC> npc);
    
    // Запуск боевого режима
    void startBattle(int range);
    
    // Печать списка NPC
    void printNPCs() const;
    
    // Сохранение в файл
    void saveToFile(const std::string& filename) const;
    
    // Загрузка из файла
    void loadFromFile(const std::string& filename);
    
    // Добавление наблюдателя
    void addObserver(std::shared_ptr<Observer> observer);
    
private:
    std::vector<std::unique_ptr<NPC>> npcs_;
    std::vector<std::shared_ptr<Observer>> observers_;
    
    // Проверка дистанции между NPC
    bool isInRange(const NPC& npc1, const NPC& npc2, int range) const;
    
    // Метод для уведомления наблюдателей
    void notifyObservers(const std::string& message) const;
    
    // Дружественный класс для тестирования
    friend class DungeonTestHelper;
};