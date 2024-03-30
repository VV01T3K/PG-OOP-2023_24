#pragma once

class Ability {
   private:
    const int default_cooldown;
    const int default_duration;
    int cooldown = 0;
    int duration = 0;

   public:
    Ability(int cooldown, int duration)
        : default_cooldown(cooldown), default_duration(duration) {}
    Ability(int cooldown, int duration, int default_cooldown,
            int default_duration)
        : cooldown(cooldown),
          duration(duration),
          default_cooldown(default_cooldown),
          default_duration(default_duration) {}
    ~Ability() = default;

    bool isReady() { return cooldown == 0; }
    bool isActive() { return duration > 0; }

    int getCooldown() const { return cooldown; }
    int getDuration() const { return duration; }

    void use() {
        if (isReady() && !isActive()) {
            cooldown = default_cooldown;
            duration = default_duration;
        }
    }
    void update() {
        if (duration > 0) {
            duration--;
        } else if (cooldown > 0) {
            cooldown--;
        }
    }

    virtual void effect(Organism& user, Organism& other) = 0;
};
