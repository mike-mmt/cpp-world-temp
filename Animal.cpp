#pragma once
#include "Organism.cpp"
class Animal : public Organism {
public:
    static const int BASE_LIFE_LEFT = 10;
    static const int LIFE_LEFT_VARIANCE = 3;

    Animal(int power, const std::string& species, Position* position, int birthTurn, int initiative) :
            Organism(power, species, position, birthTurn, initiative) {}

    Animal(int power, Position* position, int birthTurn, int initiative) :
            Organism(power, "A", position, birthTurn, initiative) {
    }

    Animal(const Organism& other, Position* birthPosition, int birthTurn) :
            Organism(other, birthPosition, birthTurn) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
        initiative = other.getInitiative();
        position = new Position(*birthPosition);
    }

    void setPosition(Position* newPosition) { this->position = newPosition; }
};
