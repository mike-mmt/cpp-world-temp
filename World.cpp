#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include "Organism.cpp"
#include "Position.cpp"
#include "Animal.cpp"
#include "Toadstool.cpp"
#include "Position.cpp"

class World {
public:
    World(int worldWidth = 10, int worldHeight = 10) :
            worldWidth(worldWidth), worldHeight(worldHeight), turn(0), organisms() {
    }

    int getWorldWidth() const { return worldWidth; }
    int getWorldHeight() const { return worldHeight; }
    int getTurn() const { return turn; }

    void makeTurn() {
        turn++;

        std::vector<Organism*> newOrganisms;

        // Create a copy of organisms to avoid iterator invalidation during update
        std::vector<Organism*> oldOrganisms(organisms.begin(), organisms.end());
        for (Organism* o : oldOrganisms) {
            o->setPower(o->getPower() + 1);

            // Handle movement and fight logic (assuming Animal is a derived class)
            if (dynamic_cast<Animal*>(o)) {
                auto position = o->getPosition();
                auto possiblePositions = getListOfPossiblePositions(*position);
                if (!possiblePositions.empty()) {
                    auto randomPosition = possiblePositions[std::rand() % possiblePositions.size()];
                    if (isPositionFree(randomPosition)) {
                        dynamic_cast<Animal*>(o)->setPosition(new Position(randomPosition));
                    } else {  // Fight
                        Organism* enemyOrganism = getOrganismFromPosition(randomPosition);
                        if (o->getInitiative() > enemyOrganism->getInitiative()) {
                            if (dynamic_cast<Toadstool*>(enemyOrganism)) {
                                o->die(turn);
                                organisms.erase(std::remove(organisms.begin(), organisms.end(), o), organisms.end());
                            } else {
                                // Kill enemy and take its place
                                enemyOrganism->die(turn);
                                organisms.erase(std::remove(organisms.begin(), organisms.end(), enemyOrganism), organisms.end());
                                static_cast<Animal*>(o)->setPosition(&randomPosition);
                            }
                        }
                    }
                }
            }

            // Reproduce logic
            auto freePositions = getListOfFreePositions(*o->getPosition());
            Organism* child = o->reproduce(turn, freePositions);
            if (child) {
                newOrganisms.push_back(std::move(child));
            }

            o->setLifeLeft(o->getLifeLeft() - 1);
            if (o->getLifeLeft() <= 0) {
                o->die(turn);
                organisms.erase(std::remove(organisms.begin(), organisms.end(), o), organisms.end());
            }
        }
        organisms.insert(organisms.end(), newOrganisms.begin(), newOrganisms.end());
        newOrganisms.clear();
        oldOrganisms.clear();
    }

    void addOrganism(Organism* organism) {
        organisms.push_back(std::move(organism));
    }

    const std::vector<Organism*>& getOrganisms() const { return organisms; }

    std::string getOrganismSpeciesFromPosition(int x, int y) const {
        Position position(x, y);
        for (const Organism* organism : organisms) {
            if (organism->getPosition()->equals(position)) {
                return organism->getSpecies();
            }
        }
        return " ";
    }

    Organism* getOrganismFromPosition(int x, int y) const {
        Position position(x, y);
        for (const Organism* organism : organisms) {
            if (organism->getPosition()->equals(position)) {
                return const_cast<Organism*>(organism); // This can be unsafe if modifying the organism outside World
            }
        }
        return nullptr;
    }

    Organism* getOrganismFromPosition(const Position& position) const {
        for (const Organism* organism : organisms) {
            if (organism->getPosition()->equals(position)) {
                return const_cast<Organism*>(organism); // Same safety concern as above
            }
        }
        return nullptr;
    }

    bool isPositionOnWorld(int x, int y) const {
        return x >= 0 && x < worldWidth && y >= 0 && y < worldHeight;
    }

    bool isPositionFree(const Position& position) const {
        for (const Organism* organism : organisms) {
            if (organism->getPosition()->equals(position)) {
                return false;
            }
        }
        return true;
    }

    std::vector<Position> getListOfFreePositions(const Position& position) const {
        int pos_x = position.getX();
        int pos_y = position.getY();
        std::vector<Position> freePositions;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
                    Position newPosition(pos_x + x, pos_y + y);
                    if (isPositionFree(newPosition)) {
                        freePositions.push_back(newPosition);
                    }
                }
            }
        }
        return freePositions;
    }

    std::vector<Position> getListOfPossiblePositions(const Position& position) const {
        int pos_x = position.getX();
        int pos_y = position.getY();
        std::vector<Position> possiblePositions;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (isPositionOnWorld(pos_x + x, pos_y + y)) {
                    possiblePositions.emplace_back(pos_x + x, pos_y + y); // Use emplace_back for potential performance benefit
                }
            }
        }
        return possiblePositions;
    }

    std::string toString() const {
        std::string worldString;
        for (int x = 0; x < worldWidth; x++) {
            for (int y = 0; y < worldHeight; y++) {
                worldString += getOrganismSpeciesFromPosition(x, y);
                worldString.push_back('.');
            }
            worldString.push_back('\n');
        }
        return worldString;
    }

private:
    int worldWidth;
    int worldHeight;
    int turn;
    std::vector<Organism*> organisms;
};