#include "../include/npc.h"
#include <random>
#include <cmath>
#include <vector>

std::string get_random_npc_type() {
    static std::vector<std::string> types;
    if (types.empty()) {
        for (const auto& pair : NPC_TYPES) {
            types.push_back(pair.first);
        }
    }
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, types.size() - 1);
    return types[dist(rng)];
}

double calculate_distance(const NPC& a, const NPC& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

bool can_attack(const NPC& attacker, const NPC& target) {
    if (attacker.type == "Pegasus") {
        return false;
    }
    
    if (attacker.type == "Dragon" && target.type == "Pegasus") {
        return true;
    }
    
    if (attacker.type == "Knight" && target.type == "Dragon") {
        return true;
    }
    
    return false;
}

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}