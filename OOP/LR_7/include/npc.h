#pragma once
#include <string>
#include <map>

struct NPCStats {
    int move_distance;
    int kill_distance;
};

extern const std::map<std::string, NPCStats> NPC_TYPES;

struct NPC {
    std::string type;
    int x, y;
    bool alive = true;
    NPCStats stats;
};

std::string get_random_npc_type();
double calculate_distance(const NPC& a, const NPC& b);
bool can_attack(const NPC& attacker, const NPC& target);
int clamp(int value, int min, int max);