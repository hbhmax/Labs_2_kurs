#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/constants.h"

TEST(NPCTest, CalculateDistance) {
    NPC a{"Knight", 0, 0};
    NPC b{"Dragon", 3, 4};
    
    double dist = calculate_distance(a, b);
    EXPECT_DOUBLE_EQ(dist, 5.0);
}

TEST(NPCTest, ClampFunction) {
    EXPECT_EQ(clamp(5, 0, 10), 5);
    EXPECT_EQ(clamp(-5, 0, 10), 0);
    EXPECT_EQ(clamp(15, 0, 10), 10);
}

TEST(NPCTest, CanAttackRules) {
    NPC knight{"Knight", 0, 0};
    NPC pegasus{"Pegasus", 0, 0};
    NPC dragon{"Dragon", 0, 0};

    EXPECT_FALSE(can_attack(pegasus, knight));
    EXPECT_FALSE(can_attack(pegasus, dragon));
    EXPECT_FALSE(can_attack(pegasus, pegasus));

    EXPECT_TRUE(can_attack(dragon, pegasus));
    EXPECT_FALSE(can_attack(dragon, knight));

    EXPECT_TRUE(can_attack(knight, dragon));
    EXPECT_FALSE(can_attack(knight, pegasus));
    EXPECT_FALSE(can_attack(knight, knight));
}

TEST(NPCTest, NPCTypesStats) {
    EXPECT_EQ(NPC_TYPES.size(), 3);
    
    EXPECT_EQ(NPC_TYPES.at("Knight").move_distance, 30);
    EXPECT_EQ(NPC_TYPES.at("Knight").kill_distance, 10);
    
    EXPECT_EQ(NPC_TYPES.at("Pegasus").move_distance, 30);
    EXPECT_EQ(NPC_TYPES.at("Pegasus").kill_distance, 10);
    
    EXPECT_EQ(NPC_TYPES.at("Dragon").move_distance, 50);
    EXPECT_EQ(NPC_TYPES.at("Dragon").kill_distance, 30);
}

TEST(NPCTest, RandomNPCType) {
    std::string type = get_random_npc_type();
    EXPECT_TRUE(type == "Knight" || type == "Pegasus" || type == "Dragon");
}

TEST(ConstantsTest, MapDimensions) {
    EXPECT_EQ(MAP_WIDTH, 100);
    EXPECT_EQ(MAP_HEIGHT, 100);
    EXPECT_EQ(NPC_COUNT, 50);
    EXPECT_EQ(RUN_TIME_SECONDS, 30);
}

TEST(NPCTest, NPCInitialization) {
    NPC npc{"Knight", 10, 20};
    npc.stats = NPC_TYPES.at("Knight");
    
    EXPECT_EQ(npc.type, "Knight");
    EXPECT_EQ(npc.x, 10);
    EXPECT_EQ(npc.y, 20);
    EXPECT_TRUE(npc.alive);
    EXPECT_EQ(npc.stats.move_distance, 30);
    EXPECT_EQ(npc.stats.kill_distance, 10);
}