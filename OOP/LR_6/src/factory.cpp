#include "../include/factory.h"
#include <sstream>
#include <iostream>

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string& type, 
                                          const std::string& name, 
                                          int x, 
                                          int y) {
    if (type == "Knight") {
        return createKnight(name, x, y);
    }
    else if (type == "Squirrel") {
        return createSquirrel(name, x, y);
    }
    else if (type == "Pegasus") {
        return createPegasus(name, x, y);
    }
    
    std::cerr << "Error: unknown NPC type " << type << std::endl;
    return nullptr;
}

std::unique_ptr<NPC> NPCFactory::loadNPC(const std::string& data) {
    std::stringstream ss(data);
    std::string type, name;
    int x, y;
    
    if (!(ss >> type >> name >> x >> y)) {
        std::cerr << "Data format error when loading NPC: " << data << std::endl;
        return nullptr;
    }
    
    std::string extra;
    if (ss >> extra) {
        std::cerr << "Extra data in line when loading NPC: " << data << std::endl;
        return nullptr;
    }
    
    return createNPC(type, name, x, y);
}

std::unique_ptr<Knight> NPCFactory::createKnight(const std::string& name, int x, int y) {
    return std::make_unique<Knight>(name, x, y);
}

std::unique_ptr<Squirrel> NPCFactory::createSquirrel(const std::string& name, int x, int y) {
    return std::make_unique<Squirrel>(name, x, y);
}

std::unique_ptr<Pegasus> NPCFactory::createPegasus(const std::string& name, int x, int y) {
    return std::make_unique<Pegasus>(name, x, y);
}