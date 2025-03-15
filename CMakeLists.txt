cmake_minimum_required(VERSION 3.28)
project(bluffjack)

set(CMAKE_CXX_STANDARD 17)

add_executable(bluffjack main.cpp
        card.cpp
        card.h
        deck.cpp
        deck.h
        player.cpp
        player.h
        pot.cpp
        pot.h
        table.cpp
        table.h)
