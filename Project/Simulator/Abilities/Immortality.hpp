#pragma once

#include "../Tile.hpp"
#include "@Ability.hpp"

class Organism;
class Immortality : public Ability {
   public:
    Immortality(int cooldown, int duration) : Ability(cooldown, duration) {}
    Immortality(int cooldown, int duration, int default_cooldown,
                int default_duration)
        : Ability(cooldown, duration, 5, 5) {}
    ~Immortality() = default;

    void effect(Organism& user, Organism& other);
};