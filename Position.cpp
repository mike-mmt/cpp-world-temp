#pragma once
#include <string>

class Position {
public:
    Position(int x, int y) : x(x), y(y) {}

    int getX() const { return x; }
    void setX(int x) { this->x = x; }

    int getY() const { return y; }
    void setY(int y) { this->y = y; }

    void moveRelative(int dx, int dy) {
        x += dx;
        y += dy;
    }

    std::string toString() const {
        return "Position [x=" + std::to_string(x) + ", y=" + std::to_string(y) + "]";
    }

    bool equals(const Position& other) const {
        return (x == other.getX()) && (y == other.getY());
    }

private:
    int x;
    int y;
};
