#include "include/dungeon.h"
#include "include/observer.h"
#include "include/factory.h"
#include <iostream>
#include <string>

int main() {
    Dungeon dungeon;

    std::shared_ptr<ConsoleObserver> consoleObserver = std::make_shared<ConsoleObserver>();
    std::shared_ptr<FileObserver> fileObserver = std::make_shared<FileObserver>("log.txt");

    dungeon.addObserver(consoleObserver);
    dungeon.addObserver(fileObserver);

    dungeon.addNPC(NPCFactory::createNPC("Knight", "Knight Arthur", 100, 100));
    dungeon.addNPC(NPCFactory::createNPC("Squirrel", "Squirrel Lucy", 150, 150));
    dungeon.addNPC(NPCFactory::createNPC("Pegasus", "Pegasus Silver", 200, 200));

    std::cout << "\nNPC list in dungeon:\n";
    dungeon.printNPCs();

    dungeon.saveToFile("save.txt");
    std::cout << "\nData successfully saved to save.txt\n";

    dungeon.loadFromFile("save.txt");
    std::cout << "\nData successfully loaded from save.txt\n";

    std::cout << "\nStarting battle mode (battle radius 100 meters)\n";
    dungeon.startBattle(100);

    std::cout << "\nRemaining NPCs after battle:\n";
    dungeon.printNPCs();

    return 0;
}