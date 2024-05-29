#pragma once
#include "Animal.cpp"
#include "iostream"
class Wolf : public Animal {
public:
    static const int BASE_LIFE_LEFT = 20;
    static const int LIFE_LEFT_VARIANCE = 4;
    static const int POWER_TO_REPRODUCE = 13;

    Wolf(int power, const std::string& species, Position* position, int birthTurn, int initiative) :
            Animal(power, species, position, birthTurn, initiative) {}

    Wolf(int power, Position* position, int birthTurn) :
            Animal(power, "W", position, birthTurn, 5) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
    }

    Wolf(Position* position, int birthTurn) :
            Animal(6, "W", position, birthTurn, 3) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
    }

    Wolf(const Organism& other, Position* birthPosition, int birthTurn) : Animal(other, birthPosition, birthTurn) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
        initiative = other.getInitiative();
    }

    Wolf* reproduce(int currentTurn, const std::vector<Position>& freePositions) override {
        if (getPower() >= POWER_TO_REPRODUCE && !freePositions.empty()) {
            auto randomPosition = freePositions[std::rand() % freePositions.size()];
            Wolf* child = new Wolf(*this, &randomPosition, currentTurn);
            children.push_back(std::move(child));
            setPower(1);
            return child;
        }
        return nullptr;
    }
};
