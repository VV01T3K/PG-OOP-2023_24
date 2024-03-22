#pragma once

#include <cstdint>
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
};