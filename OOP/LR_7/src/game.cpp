#include "../include/game.h"
#include "constants.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <unordered_set>
#include <algorithm>

const std::map<std::string, NPCStats> NPC_TYPES = {
    {"Knight", {30, 10}},
    {"Pegasus", {30, 10}},
    {"Dragon", {50, 30}}
};

std::shared_mutex npc_mutex;
std::mutex cout_mutex;
std::mutex battle_queue_mutex;

std::vector<NPC> npcs;
std::queue<std::pair<int, int>> battle_queue;
std::set<std::pair<int, int>> active_battles;

void init_npcs() {
    std::set<std::pair<int, int>> used_positions;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist_pos(0, MAP_WIDTH - 1);
    
    for (int i = 0; i < NPC_COUNT; i++) {
        NPC npc;
        npc.type = get_random_npc_type();
        npc.stats = NPC_TYPES.at(npc.type);
        
        int attempts = 0;
        do {
            npc.x = clamp(dist_pos(rng), 0, MAP_WIDTH - 1);
            npc.y = clamp(dist_pos(rng), 0, MAP_HEIGHT - 1);
            attempts++;
        } while (used_positions.count({npc.x, npc.y}) > 0 && attempts < 100);
        
        if (attempts >= 100) {
            continue;
        }
        
        used_positions.insert({npc.x, npc.y});
        npc.alive = true;
        npcs.push_back(npc);
    }
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void movement_and_battle_thread(std::atomic<bool>& running) {
    std::mt19937 local_rng(std::random_device{}());
    std::uniform_int_distribution<int> dist_move(-1, 1);
    
    while (running.load()) {
        {
            std::unique_lock lock(npc_mutex);
            
            std::unordered_set<int> occupied_positions;
            for (const auto& npc : npcs) {
                if (npc.alive) {
                    occupied_positions.insert(npc.y * MAP_WIDTH + npc.x);
                }
            }
            
            for (size_t i = 0; i < npcs.size(); i++) {
                auto& npc = npcs[i];
                if (!npc.alive) continue;
                
                int old_x = npc.x;
                int old_y = npc.y;
                
                int move_x = dist_move(local_rng) * npc.stats.move_distance;
                int move_y = dist_move(local_rng) * npc.stats.move_distance;
                
                int new_x = clamp(npc.x + move_x, 0, MAP_WIDTH - 1);
                int new_y = clamp(npc.y + move_y, 0, MAP_HEIGHT - 1);
                
                int new_pos_key = new_y * MAP_WIDTH + new_x;
                if (occupied_positions.count(new_pos_key) == 0) {
                    occupied_positions.erase(old_y * MAP_WIDTH + old_x);
                    occupied_positions.insert(new_pos_key);
                    
                    npc.x = new_x;
                    npc.y = new_y;
                }
                
                for (size_t j = i + 1; j < npcs.size(); j++) {
                    auto& other_npc = npcs[j];
                    if (!other_npc.alive) continue;
                    
                    double distance = calculate_distance(npc, other_npc);
                    
                    if (can_attack(npc, other_npc) && distance <= npc.stats.kill_distance) {
                        std::lock_guard battle_lock(battle_queue_mutex);
                        
                        std::pair<int, int> battle_pair = {static_cast<int>(i), static_cast<int>(j)};
                        std::pair<int, int> reverse_pair = {static_cast<int>(j), static_cast<int>(i)};
                        
                        if (active_battles.find(battle_pair) == active_battles.end() && 
                            active_battles.find(reverse_pair) == active_battles.end()) {
                            battle_queue.push(battle_pair);
                            active_battles.insert(battle_pair);
                        }
                    }
                    
                    if (can_attack(other_npc, npc) && distance <= other_npc.stats.kill_distance) {
                        std::lock_guard battle_lock(battle_queue_mutex);
                        
                        std::pair<int, int> battle_pair = {static_cast<int>(j), static_cast<int>(i)};
                        std::pair<int, int> reverse_pair = {static_cast<int>(i), static_cast<int>(j)};
                        
                        if (active_battles.find(battle_pair) == active_battles.end() && 
                            active_battles.find(reverse_pair) == active_battles.end()) {
                            battle_queue.push(battle_pair);
                            active_battles.insert(battle_pair);
                        }
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void battle_thread(std::atomic<bool>& running) {
    std::mt19937 local_rng(std::random_device{}());
    std::uniform_int_distribution<int> dist_dice_local(1, 6);
    
    while (running.load()) {
        std::queue<std::pair<int, int>> local_battle_queue;
        
        {
            std::lock_guard lock(battle_queue_mutex);
            local_battle_queue.swap(battle_queue);
            active_battles.clear();
        }
        
        while (!local_battle_queue.empty()) {
            auto [attacker_idx, defender_idx] = local_battle_queue.front();
            local_battle_queue.pop();
            
            std::unique_lock lock(npc_mutex);
            
            if (attacker_idx < npcs.size() && defender_idx < npcs.size() && 
                npcs[attacker_idx].alive && npcs[defender_idx].alive) {
                
                NPC& attacker = npcs[attacker_idx];
                NPC& defender = npcs[defender_idx];
                
                if (!can_attack(attacker, defender)) {
                    continue; 
                }
                
                int attack_roll = dist_dice_local(local_rng);
                int defense_roll = dist_dice_local(local_rng);
                
                {
                    std::lock_guard cout_lock(cout_mutex);
                    std::cout << "FIGHT: " << attacker.type << " [" << attack_roll 
                              << "] vs " << defender.type << " [" << defense_roll << "]";
                }
                
                if (attack_roll > defense_roll) {
                    defender.alive = false;
                    {
                        std::lock_guard cout_lock(cout_mutex);
                        std::cout << " -> " << defender.type << " KILLED!" << std::endl;
                    }
                } else {
                    {
                        std::lock_guard cout_lock(cout_mutex);
                        std::cout << " -> " << defender.type << " SURVIVED!" << std::endl;
                    }
                }
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void print_initial_map() {
    std::shared_lock lock(npc_mutex);
    std::lock_guard cout_lock(cout_mutex);
    
    clear_screen();
    
    int alive_count = 0;
    for (const auto& npc : npcs) {
        if (npc.alive) {
            alive_count++;
        }
    }
    
    std::cout << "\n=== INITIAL MAP 100x100 (" << alive_count << " NPCs) ===" << std::endl;
    
    std::vector<std::vector<char>> full_map(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, '.'));
    
    for (const auto& npc : npcs) {
        if (npc.alive) {
            char symbol = '.';
            if (npc.type == "Knight") symbol = 'K';
            else if (npc.type == "Pegasus") symbol = 'P';
            else if (npc.type == "Dragon") symbol = 'D';
            
            if (npc.x >= 0 && npc.x < MAP_WIDTH && npc.y >= 0 && npc.y < MAP_HEIGHT) {
                full_map[npc.y][npc.x] = symbol;
            }
        }
    }
    
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            std::cout << full_map[y][x];
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nLEGEND: K=Knight, P=Pegasus, D=Dragon" << std::endl;
    std::cout << "RULES: Pegasus doesn't attack; Dragon eats Pegasus; Knight kills Dragon" << std::endl;
    
    std::cout << "\nInitial NPC positions:" << std::endl;
    int displayed = 0;
    for (const auto& npc : npcs) {
        if (npc.alive) {
            std::cout << npc.type << "(" << npc.x << "," << npc.y << ") ";
            displayed++;
            if (displayed % 3 == 0) std::cout << std::endl;
        }
    }
    if (displayed == 0) {
        std::cout << "None";
    }
    if (displayed % 3 != 0) std::cout << std::endl;
    std::cout << "==========================" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void print_map_thread(std::atomic<bool>& running) {
    auto last_print_time = std::chrono::steady_clock::now();
    
    while (running.load()) {
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_print_time);
        
        if (elapsed.count() >= 1) {
            {
                std::shared_lock lock(npc_mutex);
                std::lock_guard cout_lock(cout_mutex);
                
                clear_screen();
                
                int alive_count = 0;
                for (const auto& npc : npcs) {
                    if (npc.alive) {
                        alive_count++;
                    }
                }
                
                std::cout << "\n=== FULL MAP 100x100 (" << alive_count << " survived) ===" << std::endl;
                
                std::vector<std::vector<char>> full_map(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, '.'));
                
                for (const auto& npc : npcs) {
                    if (npc.alive) {
                        char symbol = '.';
                        if (npc.type == "Knight") symbol = 'K';
                        else if (npc.type == "Pegasus") symbol = 'P';
                        else if (npc.type == "Dragon") symbol = 'D';
                        
                        if (npc.x >= 0 && npc.x < MAP_WIDTH && npc.y >= 0 && npc.y < MAP_HEIGHT) {
                            full_map[npc.y][npc.x] = symbol;
                        }
                    }
                }
                
                for (int y = 0; y < MAP_HEIGHT; y++) {
                    for (int x = 0; x < MAP_WIDTH; x++) {
                        std::cout << full_map[y][x];
                    }
                    std::cout << std::endl;
                }
                
                std::cout << "\nLEGEND: K=Knight, P=Pegasus, D=Dragon" << std::endl;
                std::cout << "RULES: Pegasus doesn't attack; Dragon eats Pegasus; Knight kills Dragon" << std::endl;
                
                std::cout << "\nAlive NPC positions:" << std::endl;
                int displayed = 0;
                for (const auto& npc : npcs) {
                    if (npc.alive) {
                        std::cout << npc.type << "(" << npc.x << "," << npc.y << ") ";
                        displayed++;
                        if (displayed % 3 == 0) std::cout << std::endl;
                    }
                }
                if (displayed == 0) {
                    std::cout << "None";
                }
                if (displayed % 3 != 0) std::cout << std::endl;
                std::cout << "==========================" << std::endl;
            }
            
            last_print_time = current_time;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}