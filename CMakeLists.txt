cmake_minimum_required(VERSION 3.27)
project(my_living_world)

set(CMAKE_CXX_STANDARD 20)

add_executable(my_living_world main.cpp
        Organism.cpp
        Position.cpp
        Ancestor.cpp
        World.cpp
        Animal.cpp
        Plant.cpp
        Dandelion.cpp
        Sheep.cpp
        Wolf.cpp
        Grass.cpp
        Toadstool.cpp)
