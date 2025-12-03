#pragma once
#include "npc.h"
#include <string>
#include <memory>

class NPCFactory {
public:
    // Создание NPC по типу и координатам
    static std::unique_ptr<NPC> createNPC(const std::string& type, 
                                         const std::string& name, 
                                         int x, 
                                         int y);
    
    // Загрузка NPC из строки (для загрузки из файла)
    static std::unique_ptr<NPC> loadNPC(const std::string& data);
    
private:
    // Вспомогательные функции для создания конкретных типов
    static std::unique_ptr<Knight> createKnight(const std::string& name, int x, int y);
    static std::unique_ptr<Squirrel> createSquirrel(const std::string& name, int x, int y);
    static std::unique_ptr<Pegasus> createPegasus(const std::string& name, int x, int y);
};