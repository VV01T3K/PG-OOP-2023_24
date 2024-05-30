package Simulator.Organisms.Animals;

import Simulator.World;

import org.json.JSONObject;

public class Wolf extends Animal {
    public Wolf(World world) {
        super(9, 5, world, Type.WOLF);
    }

    public Wolf(JSONObject json, World world) {
        super(json, world);
    }

    @Override
    public Animal construct() {
        return new Wolf(world);
    }
}