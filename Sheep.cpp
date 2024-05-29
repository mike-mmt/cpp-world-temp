#pragma once
#include "Animal.cpp"
class Sheep : public Animal {
public:
    static const int BASE_LIFE_LEFT = 10;
    static const int LIFE_LEFT_VARIANCE = 2;
    static const int POWER_TO_REPRODUCE = 6;

    Sheep(int power, const std::string& species, Position* position, int birthTurn, int initiative) :
            Animal(power, species, position, birthTurn, initiative) {}

    Sheep(int power, Position* position, int birthTurn) :
            Animal(power, "S", position, birthTurn, 5) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
    }

    Sheep(Position* position, int birthTurn) :
            Animal(3, "S", position, birthTurn, 3) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
    }

    Sheep(const Organism& other, Position* birthPosition, int birthTurn) :
            Animal(other, birthPosition, birthTurn) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
        initiative = other.getInitiative();
    }

    Sheep* reproduce(int currentTurn, const std::vector<Position>& freePositions) override {
        if (getPower() >= POWER_TO_REPRODUCE && !freePositions.empty()) {
            auto randomPosition = freePositions[std::rand() % freePositions.size()];
            Sheep* child = new Sheep(*this, &randomPosition, currentTurn);
            children.push_back(std::move(child));
            setPower(1);
            return child;
        }
        return nullptr;
    }
};
