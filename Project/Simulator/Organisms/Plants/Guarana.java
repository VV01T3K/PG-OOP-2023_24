package Simulator.Organisms.Plants;

import Simulator.Organisms.Organism;
import Simulator.World;

public class Guarana extends Plant {

    public Guarana(World world) {
        super(0, world, Type.GUARANA);
    }

    @Override
    public Plant construct() {
        return new Guarana(world);
    }

    @Override
    public boolean collisionReaction(Organism other) {
        other.setPower(other.getPower() + 3);
        die();
        world.addLog(other.getSymbol() + " ate " + getSymbol() + " and gained 3 power!");
        return true;
    }
}