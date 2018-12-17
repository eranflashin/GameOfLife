cmake_minimum_required(VERSION 3.13)
project(OSHw3)

set(CMAKE_CXX_STANDARD 11)

add_executable(OSHw3 Code_Skeleton/Part1/tests/semaphore_test.cpp Code_Skeleton/Part1/Semaphore.cpp Code_Skeleton/Part1/PCQueue.hpp)

target_link_libraries(OSHw3 pthread)
