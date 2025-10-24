cmake_minimum_required(VERSION 3.10)
project(Figures)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(${CMAKE_PROJECT_NAME}_lib
    include/Figure.h
    include/Rhombus.h
    include/Pentagon.h
    include/Hexagon.h
    include/FigureArray.h
    src/Figure.cpp
    src/Rhombus.cpp
    src/Pentagon.cpp
    src/Hexagon.cpp
    src/FigureArray.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME}_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

enable_testing()

add_executable(tests test/tests.cpp)
target_link_libraries(tests PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest_main)

add_test(NAME FiguresTests COMMAND tests)