package Simulator.Organisms.Plants;

import Simulator.Organisms.Organism;

import org.json.JSONObject;

import Simulator.World;

public class WolfBerries extends Plant {

    public WolfBerries(World world) {
        super(99, world, Type.WOLF_BERRIES);
    }

    public WolfBerries(JSONObject json, World world) {
        super(json, world);
    }

    @Override
    public Plant construct() {
        return new WolfBerries(world);
    }

    @Override
    public boolean collisionReaction(Organism other) {
        other.die();
        die();
        world.addLog(other.getSymbol() + " ate " + getSymbol() + " and died!");
        return true;
    }
}