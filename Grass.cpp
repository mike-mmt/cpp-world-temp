#pragma once
#include "Plant.cpp"

class Grass : public Plant {
public:
    static const int BASE_LIFE_LEFT = 12;
    static const int LIFE_LEFT_VARIANCE = 1;
    static const int POWER_TO_REPRODUCE = 4;

    Grass(int power, const std::string& species, Position* position, int birthTurn, int initiative) :
            Plant(power, species, position, birthTurn, initiative) {}

    Grass(int power, Position* position, int birthTurn) :
            Plant(power, "G", position, birthTurn, 0) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
    }

    Grass(Position* position, int birthTurn) :
            Plant(1, "G", position, birthTurn, 0) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
    }

    Grass(const Organism& other, Position* birthPosition, int birthTurn) :
            Plant(other, birthPosition, birthTurn) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
        initiative = other.getInitiative();
    }

    Grass* reproduce(int currentTurn, const std::vector<Position>& freePositions) override {
        if (getPower() >= POWER_TO_REPRODUCE && !freePositions.empty()) {
            auto randomPosition = freePositions[std::rand() % freePositions.size()];
            Grass* child = new Grass(*this, &randomPosition, currentTurn);
            children.push_back(std::move(child));
            setPower(1);
            return child;
        }
        return nullptr;
    }
};
