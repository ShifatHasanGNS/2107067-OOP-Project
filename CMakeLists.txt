cmake_minimum_required(VERSION 3.26)
project(Tunneler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tunneler main.cpp
        include/Terminal.cpp
        include/GameState.cpp
        src/Game.cpp
        include/headers.h
)





