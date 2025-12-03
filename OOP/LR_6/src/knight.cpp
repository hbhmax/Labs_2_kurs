#include "../include/npc.h"
#include "../include/visitor.h"

void Knight::accept(Visitor& visitor) {
    visitor.visit(*this);
}

bool Knight::canAttack(const NPC& other) const {
    return dynamic_cast<const Squirrel*>(&other) != nullptr;
}