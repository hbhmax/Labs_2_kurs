#pragma once
#include <atomic>
#include <vector>
#include <queue>
#include <set>
#include <mutex>
#include <shared_mutex>
#include "npc.h"

extern std::shared_mutex npc_mutex;
extern std::mutex cout_mutex;
extern std::mutex battle_queue_mutex;

extern std::vector<NPC> npcs;
extern std::queue<std::pair<int, int>> battle_queue;
extern std::set<std::pair<int, int>> active_battles;

void init_npcs();
void movement_and_battle_thread(std::atomic<bool>& running);
void battle_thread(std::atomic<bool>& running);
void print_initial_map();
void print_map_thread(std::atomic<bool>& running);
void clear_screen();
