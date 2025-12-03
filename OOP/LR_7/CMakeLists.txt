cmake_minimum_required(VERSION 3.10)
project(NPCBattleSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(npc_battle_lib
    src/game.cpp
    src/npc.cpp
)

target_include_directories(npc_battle_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(npc_battle_lib Threads::Threads)

add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE npc_battle_lib)

enable_testing()

add_executable(tests test/tests.cpp)
target_link_libraries(tests PRIVATE npc_battle_lib gtest_main)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_test(NAME NPCBattleTests COMMAND tests)