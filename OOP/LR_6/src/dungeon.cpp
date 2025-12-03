#include "../include/dungeon.h"
#include "../include/factory.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>

void Dungeon::addNPC(std::unique_ptr<NPC> npc) {
    npcs_.push_back(std::move(npc));
}

bool Dungeon::isInRange(const NPC& npc1, const NPC& npc2, int range) const {
    int dx = npc1.getX() - npc2.getX();
    int dy = npc1.getY() - npc2.getY();
    return dx * dx + dy * dy <= range * range;
}

void Dungeon::printNPCs() const {
    for (const auto& npc : npcs_) {
        std::cout << "Type: " << npc->getType() << " | Name: " << npc->getName()
                  << " | Coordinates: (" << npc->getX() << ", " << npc->getY() << ")\n";
    }
}

void Dungeon::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing\n";
        return;
    }
    
    for (const auto& npc : npcs_) {
        file << npc->getType() << " " 
             << npc->getName() << " " 
             << npc->getX() << " " 
             << npc->getY() << "\n";
    }
    file.close();
}

void Dungeon::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading\n";
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        auto npc = NPCFactory::loadNPC(line);
        if (npc) {
            addNPC(std::move(npc));
        }
    }
    file.close();
}

void Dungeon::addObserver(std::shared_ptr<Observer> observer) {
    observers_.push_back(observer);
}

void Dungeon::notifyObservers(const std::string& message) const {
    for (const auto& observer : observers_) {
        observer->update(message);
    }
}

void Dungeon::startBattle(int range) {
    std::vector<std::unique_ptr<NPC>> survivors;
    std::vector<bool> killed(npcs_.size(), false);
    
    for (size_t i = 0; i < npcs_.size(); ++i) {
        if (killed[i] || !npcs_[i]) continue;
        
        for (size_t j = 0; j < npcs_.size(); ++j) {
            if (i == j || killed[j] || !npcs_[j]) continue;
            
            if (isInRange(*npcs_[i], *npcs_[j], range)) {
                if (npcs_[j]->canAttack(*npcs_[i])) {
                    AttackVisitor attackerVisitor(npcs_[j].get());
                    
                    for (const auto& observer : observers_) {
                        attackerVisitor.addObserver(observer);
                    }
                    
                    npcs_[i]->accept(attackerVisitor);
                    
                    std::string message = npcs_[j]->getName() + " defeated " + npcs_[i]->getName();
                    notifyObservers(message);
                    
                    killed[i] = true;
                    break;
                }
            }
        }
    }
    
    for (size_t i = 0; i < npcs_.size(); ++i) {
        if (!killed[i] && npcs_[i]) {
            survivors.push_back(std::move(npcs_[i]));
        }
    }
    
    npcs_ = std::move(survivors);
}