#pragma once
#include "npc.h"
#include <memory>
#include <vector>

class Observer;

class Visitor {
public:
    virtual ~Visitor() = default;
    
    // Методы для каждого типа NPC
    virtual void visit(Knight& knight) = 0;
    virtual void visit(Squirrel& squirrel) = 0;
    virtual void visit(Pegasus& pegasus) = 0;
};

class AttackVisitor : public Visitor {
private:
    NPC* attacker_;
    std::vector<std::shared_ptr<Observer>> observers_;

public:
    AttackVisitor(NPC* attacker) : attacker_(attacker) {}
    
    void visit(Knight& knight) override;
    void visit(Squirrel& squirrel) override;
    void visit(Pegasus& pegasus) override;
    
    void addObserver(std::shared_ptr<Observer> observer);
    void notifyObservers(const std::string& message);
};