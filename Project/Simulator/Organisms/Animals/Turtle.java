package Simulator.Organisms.Animals;

import Simulator.Organisms.Organism;
import Utils.RNG;
import Simulator.World;

public class Turtle extends Animal {

    public Turtle(World world) {
        super(2, 1, world, Type.TURTLE);
    }

    @Override
    public Animal construct() {
        return new Turtle(world);
    }

    @Override
    public void action() {
        // 75% chance to skip turn
        if (RNG.roll(0, 100) < 75)
            return;
        super.action();
    }

    @Override
    public boolean collisionReaction(Organism other) {
        if (other instanceof Turtle)
            return false;
        if (other.getPower() < 5) {
            ((Animal) other).undoMove();
            world.addLog(other.getSymbol() + " tried to attack " + getSymbol() +
                    " but failed!");
            return true;
        }
        return false;
    }
}