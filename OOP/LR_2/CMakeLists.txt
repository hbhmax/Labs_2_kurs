cmake_minimum_required(VERSION 3.10)
project(OctalProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(Octal_lib
    src/Octal.cpp
)

target_include_directories(Octal_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
)

add_executable(main_exe main.cpp)
target_link_libraries(main_exe PRIVATE Octal_lib)

enable_testing()
add_executable(tests test/tests.cpp)
target_link_libraries(tests PRIVATE Octal_lib gtest_main)

add_test(NAME OctalTests COMMAND tests)