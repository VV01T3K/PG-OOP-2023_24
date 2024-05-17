package Simulator.Organisms.Animals;

import Simulator.World;

public class Sheep extends Animal {

    public Sheep(World world) {
        super(4, 4, world, Type.SHEEP);
    }

    @Override
    public Animal construct() {
        return new Sheep(world);
    }
}