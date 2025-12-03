#include "../include/visitor.h"
#include "../include/npc.h"
#include "../include/observer.h"
#include <iostream>

void AttackVisitor::visit(Knight& knight) {
    if (attacker_ && attacker_->canAttack(knight)) {
        std::string message = attacker_->getName() + " attacked " + knight.getName();
        notifyObservers(message);
    }
}

void AttackVisitor::visit(Squirrel& squirrel) {
    if (attacker_ && attacker_->canAttack(squirrel)) {
        std::string message = attacker_->getName() + " attacked " + squirrel.getName();
        notifyObservers(message);
    }
}

void AttackVisitor::visit(Pegasus& pegasus) {
    if (attacker_ && attacker_->canAttack(pegasus)) {
        std::string message = attacker_->getName() + " attacked " + pegasus.getName();
        notifyObservers(message);
    }
}

void AttackVisitor::addObserver(std::shared_ptr<Observer> observer) {
    observers_.push_back(observer);
}

void AttackVisitor::notifyObservers(const std::string& message) {
    for (const auto& observer : observers_) {
        observer->update(message);
    }
}