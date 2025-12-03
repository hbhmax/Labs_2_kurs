#include "include/game.h"
#include "include/constants.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    init_npcs();
    
    print_initial_map();
    
    std::atomic<bool> running(true);

    std::thread movement_thread(movement_and_battle_thread, std::ref(running));
    std::thread fight_thread(battle_thread, std::ref(running));
    std::thread printer_thread(print_map_thread, std::ref(running));

    std::this_thread::sleep_for(std::chrono::seconds(RUN_TIME_SECONDS));
    running = false;

    movement_thread.join();
    fight_thread.join();
    printer_thread.join();

    std::shared_lock lock(npc_mutex);
    std::lock_guard cout_lock(cout_mutex);
    std::cout << "\n=== GAME OVER ===" << std::endl;
    std::cout << "Survived NPC:" << std::endl;
    int survivor_count = 0;
    for (const auto& npc : npcs) {
        if (npc.alive) {
            std::cout << "- " << npc.type << " (" << npc.x << "," << npc.y << ")" << std::endl;
            survivor_count++;
        }
    }
    std::cout << "Survived: " << survivor_count << " NPC" << std::endl;
    
    return 0;
}