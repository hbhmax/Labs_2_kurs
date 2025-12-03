#include "gtest/gtest.h"
#include "../include/dungeon.h"
#include "../include/npc.h"
#include "../include/observer.h"
#include "../include/visitor.h"
#include "../include/factory.h"
#include <string>
#include <vector>
#include <fstream>

class DungeonTestHelper {
public:
    static size_t getNPCCount(const Dungeon& dungeon) {
        return dungeon.npcs_.size();
    }
    
    static bool isInRange(const Dungeon& dungeon, const NPC& npc1, const NPC& npc2, int range) {
        return dungeon.isInRange(npc1, npc2, range);
    }
};

TEST(NPCFactoryTest, CreateKnight) {
    auto knight = NPCFactory::createNPC("Knight", "TestKnight", 100, 100);
    ASSERT_NE(knight, nullptr);
    EXPECT_EQ(knight->getName(), "TestKnight");
    EXPECT_EQ(knight->getX(), 100);
    EXPECT_EQ(knight->getY(), 100);
}

TEST(NPCFactoryTest, CreateSquirrel) {
    auto squirrel = NPCFactory::createNPC("Squirrel", "TestSquirrel", 150, 150);
    ASSERT_NE(squirrel, nullptr);
    EXPECT_EQ(squirrel->getName(), "TestSquirrel");
    EXPECT_EQ(squirrel->getX(), 150);
    EXPECT_EQ(squirrel->getY(), 150);
}

TEST(NPCFactoryTest, CreatePegasus) {
    auto pegasus = NPCFactory::createNPC("Pegasus", "TestPegasus", 200, 200);
    ASSERT_NE(pegasus, nullptr);
    EXPECT_EQ(pegasus->getName(), "TestPegasus");
    EXPECT_EQ(pegasus->getX(), 200);
    EXPECT_EQ(pegasus->getY(), 200);
}

TEST(BattleLogicTest, KnightVsSquirrel) {
    Dungeon dungeon;
    auto knight = NPCFactory::createNPC("Knight", "TestKnight", 100, 100);
    auto squirrel = NPCFactory::createNPC("Squirrel", "TestSquirrel", 100, 100);
    
    dungeon.addNPC(std::move(knight));
    dungeon.addNPC(std::move(squirrel));
    
    EXPECT_EQ(DungeonTestHelper::getNPCCount(dungeon), 2);
    
    dungeon.startBattle(100);
    
    EXPECT_EQ(DungeonTestHelper::getNPCCount(dungeon), 1);
}

TEST(BattleLogicTest, SquirrelVsPegasus) {
    Dungeon dungeon;
    auto squirrel = NPCFactory::createNPC("Squirrel", "TestSquirrel", 100, 100);
    auto pegasus = NPCFactory::createNPC("Pegasus", "TestPegasus", 100, 100);
    
    dungeon.addNPC(std::move(squirrel));
    dungeon.addNPC(std::move(pegasus));
    
    EXPECT_EQ(DungeonTestHelper::getNPCCount(dungeon), 2);
    
    dungeon.startBattle(100);
    
    EXPECT_EQ(DungeonTestHelper::getNPCCount(dungeon), 1);
}

TEST(BattleLogicTest, PegasusSurvives) {
    Dungeon dungeon;
    auto pegasus1 = NPCFactory::createNPC("Pegasus", "Pegasus1", 100, 100);
    auto pegasus2 = NPCFactory::createNPC("Pegasus", "Pegasus2", 100, 100);
    
    dungeon.addNPC(std::move(pegasus1));
    dungeon.addNPC(std::move(pegasus2));
    
    dungeon.startBattle(100);
    
    EXPECT_EQ(DungeonTestHelper::getNPCCount(dungeon), 2);
}

TEST(ObserverTest, ConsoleObserver) {
    ConsoleObserver observer;
    std::string message = "Test check";
    observer.update(message);
}

TEST(ObserverTest, FileObserver) {
    FileObserver fileObserver("test.log");
    std::string message = "Test file entry";
    fileObserver.update(message);
}

TEST(SaveLoadTest, SaveAndLoad) {
    Dungeon dungeon;
    auto knight = NPCFactory::createNPC("Knight", "TestKnight", 100, 100);
    dungeon.addNPC(std::move(knight));
    dungeon.saveToFile("test_save.txt");
    
    Dungeon loadedDungeon;
    loadedDungeon.loadFromFile("test_save.txt");
    
    EXPECT_EQ(DungeonTestHelper::getNPCCount(loadedDungeon), 1);
}

TEST(DungeonTest, AddNPC) {
    Dungeon dungeon;
    auto knight = NPCFactory::createNPC("Knight", "TestKnight", 100, 100);
    auto squirrel = NPCFactory::createNPC("Squirrel", "TestSquirrel", 150, 150);
    
    dungeon.addNPC(std::move(knight));
    dungeon.addNPC(std::move(squirrel));
    
    EXPECT_EQ(DungeonTestHelper::getNPCCount(dungeon), 2);
}

TEST(DungeonTest, PrintNPCs) {
    Dungeon dungeon;
    auto knight = NPCFactory::createNPC("Knight", "TestKnight", 100, 100);
    dungeon.addNPC(std::move(knight));
    
    dungeon.printNPCs();
}

TEST(DistanceTest, InRange) {
    Dungeon dungeon;
    auto npc1 = NPCFactory::createNPC("Knight", "Test1", 100, 100);
    auto npc2 = NPCFactory::createNPC("Knight", "Test2", 150, 150);
    
    EXPECT_TRUE(DungeonTestHelper::isInRange(dungeon, *npc1, *npc2, 100));
    EXPECT_FALSE(DungeonTestHelper::isInRange(dungeon, *npc1, *npc2, 50));
}

TEST(BoundaryTest, EdgeCoordinates) {
    auto npc1 = NPCFactory::createNPC("Knight", "Edge1", 0, 0);
    auto npc2 = NPCFactory::createNPC("Knight", "Edge2", 500, 500);
    
    ASSERT_NE(npc1, nullptr);
    ASSERT_NE(npc2, nullptr);
    
    EXPECT_EQ(npc1->getX(), 0);
    EXPECT_EQ(npc1->getY(), 0);
    EXPECT_EQ(npc2->getX(), 500);
    EXPECT_EQ(npc2->getY(), 500);
}

TEST(InvalidDataTest, InvalidType) {
    auto invalidNPC = NPCFactory::createNPC("UnknownType", "Invalid", 100, 100);
    EXPECT_EQ(invalidNPC, nullptr);
}

TEST(InvalidLoadTest, CorruptedFile) {
    Dungeon dungeon;
    std::ofstream file("corrupted.txt");
    file << "InvalidData\n";
    file.close();
    
    dungeon.loadFromFile("corrupted.txt");
    EXPECT_EQ(DungeonTestHelper::getNPCCount(dungeon), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}