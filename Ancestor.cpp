#pragma once
#include <string>

class Ancestor {
public:
    Ancestor(int birthTurn) : birthTurn(birthTurn), deathTurn(-1) {}

    Ancestor(int birthTurn, int deathTurn) : birthTurn(birthTurn), deathTurn(deathTurn) {}

    int getBirthTurn() const { return birthTurn; }

    int getDeathTurn() const { return deathTurn; }

    void setDeathTurn(int deathTurn) { this->deathTurn = deathTurn; }

    std::string toString() const {
        return "Ancestor{birthTurn=" + std::to_string(birthTurn) + ", deathTurn=" + std::to_string(deathTurn) + "}";
    }

private:
    int birthTurn;
    int deathTurn;
};
