package Simulator.Organisms.Plants;

import Simulator.World;

public class Grass extends Plant {
    public Grass(World world) {
        super(0, world, Type.GRASS);
    }

    @Override
    public Plant construct() {
        return new Grass(world);
    }
}