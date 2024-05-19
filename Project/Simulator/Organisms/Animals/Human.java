package Simulator.Organisms.Animals;

import Simulator.Organisms.Organism;
import Simulator.GlobalSettings;
import Utils.DynamicDirections;
import Simulator.Abilities.Immortality;
import Simulator.World;

public class Human extends Animal {
    private DynamicDirections nextMove = DynamicDirections.get("SELF");
    private Immortality immortality;

    public Human(World world) {
        super(5, 4, world, Type.HUMAN);
        this.immortality = new Immortality(5, 5);
    }

    @Override
    public Animal construct() {
        return new Human(world);
    }

    @Override
    public void action() {
        if (GlobalSettings.HUMAN_AI) {
            immortality.use();
            immortality.update();
            super.action();
            return;
        }
        if (nextMove == DynamicDirections.get("SELF"))
            return;
        if (immortality.checkToggle()) {
            immortality.use();
            immortality.flipToggle();
        }
        immortality.update();
        move(nextMove);
        nextMove = DynamicDirections.get("SELF");
    }

    @Override
    public void collision(Organism other) {
        if (immortality.isActive()) {
            immortality.effect(this, other);
            return;
        } else
            super.collision(other);
    }

    @Override
    public boolean collisionReaction(Organism other) {
        if (immortality.isActive()) {
            immortality.effect(this, other);
            return true;
        } else
            return false;
    }

    public void setNextMove(DynamicDirections direction) {
        this.nextMove = direction;
    }

    public void toggleImmortality() {
        if (immortality.isReady() && !immortality.isActive())
            immortality.flipToggle();
    }

    // public String getNextMoveSTR() {
    // if (GlobalSettings.HUMAN_AI)
    // return "AI controlled";
    // switch (nextMove) {
    // case UP:
    // return "UP";
    // case DOWN:
    // return "DOWN";
    // case LEFT:
    // return "LEFT";
    // case RIGHT:
    // return "RIGHT";
    // default:
    // return "Pls give me direction";
    // }
    // }

    public DynamicDirections getNextMove() {
        return nextMove;
    }

    public String getAbilityInfo() {
        if (immortality.isActive())
            return immortality.getDuration() + " turns left";
        if (!immortality.isReady())
            return immortality.getCooldown() + " turns of cooldown left";
        if (immortality.checkToggle())
            return "Using next turn";
        return "Ready to use";
    }

    @Override
    public void die() {
        if (immortality.isActive()) {
            immortality.effect(this);
        } else {
            super.die();
        }
    }
}