cmake_minimum_required(VERSION 3.15)
project(hw3PartC)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -Werror -pedantic-errors -DNDEBUG")

add_executable(hw3PartC main.cpp Character.h Character.cpp Game.cpp
        Game.h Medic.cpp Medic.h Sniper.cpp Sniper.h Soldier.cpp Soldier.h
        TemArray.h Matrix.h Auxiliaries.cpp Auxiliaries.h Exceptions.h)