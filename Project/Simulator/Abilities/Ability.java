package Simulator.Abilities;

import Simulator.Organisms.Organism;

public abstract class Ability {
    private final int defaultCooldown;
    private final int defaultDuration;
    private int cooldown = 0;
    private int duration = 0;
    private boolean toggle = false;

    public Ability(int cooldown, int duration) {
        this.defaultCooldown = cooldown;
        this.defaultDuration = duration + 1;
    }

    public Ability(int cooldown, int duration, int defaultCooldown, int defaultDuration) {
        this.cooldown = cooldown;
        this.duration = duration;
        this.defaultCooldown = defaultCooldown;
        this.defaultDuration = defaultDuration;
    }

    public boolean isReady() {
        return cooldown == 0;
    }

    public boolean isActive() {
        return duration > 0;
    }

    public int getCooldown() {
        return cooldown;
    }

    public int getDuration() {
        return duration;
    }

    public boolean checkToggle() {
        return toggle;
    }

    public void flipToggle() {
        toggle = !toggle;
    }

    public void use() {
        if (isReady() && !isActive()) {
            cooldown = defaultCooldown;
            duration = defaultDuration;
        }
    }

    public void update() {
        if (duration > 0) {
            duration--;
        } else if (cooldown > 0) {
            cooldown--;
        }
    }

    public abstract void effect(Organism user, Organism other);
}