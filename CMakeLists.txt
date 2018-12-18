cmake_minimum_required(VERSION 3.13)
project(OSHw3)

set(CMAKE_CXX_STANDARD 11)

add_executable(OSHw3 Code_Skeleton/Part1/Semaphore.cpp Code_Skeleton/Part2/ThreadPool.cpp Code_Skeleton/Part2/GameThread.cpp Code_Skeleton/Part2/GameThread.h)

target_link_libraries(OSHw3 pthread)
