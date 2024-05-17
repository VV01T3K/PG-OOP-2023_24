package Simulator.Organisms.Animals;

import Simulator.World;

public class Wolf extends Animal {
    public Wolf(World world) {
        super(9, 5, world, Type.WOLF);
    }

    @Override
    public Animal construct() {
        return new Wolf(world);
    }
}