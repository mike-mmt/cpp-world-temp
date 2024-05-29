#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include "Sheep.cpp"
#include "Dandelion.cpp"
#include "World.cpp"
#include "Grass.cpp"
#include "Sheep.cpp"
#include "Wolf.cpp"

int main() {
    World world;

    // Add initial organisms
    world.addOrganism(new Grass(new Position(3, 4), world.getTurn()));
    world.addOrganism(new Grass(new Position(6, 7), world.getTurn()));
    world.addOrganism(new Sheep(new Position(5, 5), world.getTurn()));
    world.addOrganism(new Sheep(new Position(7, 8), world.getTurn()));
    world.addOrganism(new Sheep(new Position(9, 3), world.getTurn()));
    world.addOrganism(new Dandelion(new Position(7, 6), world.getTurn()));
    world.addOrganism(new Wolf(new Position(5, 5), world.getTurn()));
    world.addOrganism(new Wolf(new Position(4, 9), world.getTurn()));
    world.addOrganism(new Toadstool(new Position(5, 7), world.getTurn()));
    std::cout << "Turn " << world.getTurn() << std::endl;
    std::cout << world.toString() << std::endl;

    for (int i = 0; i < 50; ++i) {
//        for (Organism* organism : world.getOrganisms()) {
//            std::cout << organism->toString();
//        }
//        std::cout << std::endl;
        world.makeTurn();
        std::cout << "Turn " << world.getTurn() << std::endl;
        std::cout << world.toString() << std::endl;
        std::cout << std::endl;
//        for (Organism* organism : world.getOrganisms()) {
//            std::cout << organism->toString();
//        }
    }

    for (Organism* organism : world.getOrganisms()) {
        delete organism;
    }

    return 0;
}
