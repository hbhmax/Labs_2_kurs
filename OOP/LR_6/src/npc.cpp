#include "../include/npc.h"
#include "../include/visitor.h"

void Knight::accept(Visitor& visitor) {
    visitor.visit(*this);
}

bool Knight::canAttack(const NPC& other) const {
    const auto& npc = dynamic_cast<const Squirrel*>(&other);
    return npc != nullptr;
}

void Squirrel::accept(Visitor& visitor) {
    visitor.visit(*this);
}

bool Squirrel::canAttack(const NPC& other) const {
    const auto& npc = dynamic_cast<const Pegasus*>(&other);
    return npc != nullptr;
}

void Pegasus::accept(Visitor& visitor) {
    visitor.visit(*this);
}

bool Pegasus::canAttack(const NPC& other) const {
    return false;
}
