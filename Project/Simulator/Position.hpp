#pragma once

#include <cstdint>
#include <iostream>
class Position {
   public:
    int x;
    int y;
    Position(int x, int y) : x(x), y(y) {}
    Position() : x(0), y(0) {}
    bool operator==(const Position &other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Position &other) const { return !(*this == other); }
    friend std::ostream &operator<<(std::ostream &os,
                                    const Position &position) {
        os << "(" << position.x << ", " << position.y << ")";
        return os;
    }
};