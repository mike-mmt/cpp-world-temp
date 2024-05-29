#pragma once
#include <vector>
#include <random>
#include "Position.cpp"
#include "Ancestor.cpp"

class Organism {
public:
    static const int POWER_TO_REPRODUCE = 10;
    static const int LIFE_LEFT_VARIANCE = 5;
    static const int BASE_LIFE_LEFT = 15;

private:
    int power;
protected:
    int lifeLeft = 1;
    int initiative = 0;
    std::string species;
    Position* position; // Note: pointer to Position class (assuming it's defined elsewhere)
    std::vector<Ancestor> ancestorHistory;
    std::vector<Organism*> children; // Use pointers for children (assuming copy constructor)
    Ancestor myAncestorEntry;

public:
    Organism(int power, const std::string& species, Position* position, int birthTurn, int initiative) :
            power(power), species(species), position(position), ancestorHistory(),
            myAncestorEntry(birthTurn), initiative(initiative) {
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
    }

    Organism(const Organism& other, Position* birthPosition, int birthTurn) :
            power(1), species(other.species), position(birthPosition),
            ancestorHistory(other.ancestorHistory), initiative(other.initiative), myAncestorEntry(birthTurn) {
        ancestorHistory.push_back(other.myAncestorEntry);
        myAncestorEntry = Ancestor(birthTurn);
        position = birthPosition;
        lifeLeft = (std::rand() % LIFE_LEFT_VARIANCE) + BASE_LIFE_LEFT;
        initiative = other.initiative;
    }

    ~Organism() {
        delete position;
        for (auto child : children) {
            delete child;
        }
        for (auto ancestor : ancestorHistory) {
            delete &ancestor;
        }
        delete &myAncestorEntry;
    }

    int getPower() const { return power; }
    void setPower(int power) { this->power = power; }

    const std::string& getSpecies() const { return species; }
    void setSpecies(const std::string& species) { this->species = species; }

    int getInitiative() const { return initiative; }

    Position* getPosition() const { return position; }

    int getLifeLeft() const { return lifeLeft; }
    void setLifeLeft(int lifeLeft) { this->lifeLeft = lifeLeft; }

    const std::vector<Ancestor>& getAncestorHistory() const { return ancestorHistory; }

    const std::vector<Organism*>& getChildren() const { return children; }

    void die(int currentTurn) { myAncestorEntry.setDeathTurn(currentTurn); }

    virtual Organism* reproduce(int currentTurn, const std::vector<Position>& freePositions) = 0;

    std::string toString() const {
        return "Organism -> Species: " + species + " Power: " + std::to_string(power) + " Position: " + position->toString(); // Assuming Position has a toString method
    }
};
