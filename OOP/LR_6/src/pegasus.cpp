#include "../include/npc.h"
#include "../include/visitor.h"

void Pegasus::accept(Visitor& visitor) {
    visitor.visit(*this);
}

bool Pegasus::canAttack(const NPC& other) const {
    return false;
}