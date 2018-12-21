cmake_minimum_required(VERSION 3.13)
project(OSHw3)

set(CMAKE_CXX_STANDARD 11)

add_executable(OSHw3 Code_Skeleton/Part1/tests/queue_test.cpp Code_Skeleton/Part1/Semaphore.cpp Code_Skeleton/Part1/ConsumersProducerLock.cpp Code_Skeleton/Part1/ConsumersProducerLock.hpp)


#add_executable(OSHw3 Code_Skeleton/Part2/main.cpp Code_Skeleton/Part2/Game.cpp Code_Skeleton/Part2/utils.cpp Code_Skeleton/Part2/GameThread.cpp)

target_link_libraries(OSHw3 pthread)
