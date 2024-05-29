#pragma once
#include "Organism.cpp"
class Plant : public Organism {
public:
    static const int BASE_LIFE_LEFT = 10;
    static const int LIFE_LEFT_VARIANCE = 2;

    Plant(int power, const std::string& species, Position* position, int birthTurn, int initiative) :
            Organism(power, species, position, birthTurn, initiative) {}

    Plant(int power, Position* position, int birthTurn, int initiative) :
            Organism(power, "P", position, birthTurn, initiative) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
    }

    Plant(const Organism& other, Position* birthPosition, int birthTurn) :
            Organism(other, birthPosition, birthTurn) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
        initiative = other.getInitiative();
        position = new Position(*birthPosition);
    }
};
