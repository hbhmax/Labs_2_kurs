#include "../include/npc.h"
#include "../include/visitor.h"

void Squirrel::accept(Visitor& visitor) {
    visitor.visit(*this);
}

bool Squirrel::canAttack(const NPC& other) const {
    return dynamic_cast<const Pegasus*>(&other) != nullptr;
}