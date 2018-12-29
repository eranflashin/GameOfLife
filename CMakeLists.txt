cmake_minimum_required(VERSION 3.13)
project(OSHw3)

set(CMAKE_CXX_STANDARD 11)

add_executable(OSHw3 Code_Skeleton/combinedParts/main.cpp Code_Skeleton/combinedParts/board_utils.cpp Code_Skeleton/combinedParts/ConsumerThread.cpp
        Code_Skeleton/combinedParts/Game.cpp Code_Skeleton/combinedParts/utils.cpp Code_Skeleton/combinedParts/Semaphore.cpp Code_Skeleton/combinedParts/CounterBarrier.cpp Code_Skeleton/Part1/Alter/ArrayBarrier.cpp Code_Skeleton/Part1/Alter/ArrayBarrier.hpp)


target_link_libraries(OSHw3 pthread)
