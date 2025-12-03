cmake_minimum_required(VERSION 3.10)
project(DungeonEditor)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройки для больших объектов
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")

# Подключение Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
    TLS_VERIFY false
)

# Настройки для Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Создание библиотеки
add_library(dungeon_lib
    include/dungeon.h
    include/npc.h
    include/observer.h
    include/visitor.h
    include/factory.h
    src/dungeon.cpp
    src/npc.cpp
    src/knight.cpp
    src/squirrel.cpp
    src/pegasus.cpp
    src/observer.cpp
    src/visitor.cpp
    src/factory.cpp
)

# Настройка путей включения
target_include_directories(dungeon_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE dungeon_lib)

# Настройка тестирования
enable_testing()

# Создание тестового исполняемого файла
add_executable(tests test/tests.cpp)
target_link_libraries(tests PRIVATE dungeon_lib gtest_main)

# Добавление тестов
add_test(NAME DungeonTests COMMAND tests)

# Настройки для отладки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(dungeon_lib PRIVATE DEBUG_MODE)
    target_compile_options(dungeon_lib PRIVATE -Wall -Wextra)
endif()

# Настройки для релизной сборки
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(dungeon_lib PRIVATE -O3)
endif()
