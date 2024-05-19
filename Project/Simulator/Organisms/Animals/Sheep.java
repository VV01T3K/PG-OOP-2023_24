package Simulator.Organisms.Animals;

import Simulator.World;

import org.json.JSONObject;

public class Sheep extends Animal {

    public Sheep(World world) {
        super(4, 4, world, Type.SHEEP);
    }

    public Sheep(JSONObject json, World world) {
        super(json, world);
    }

    @Override
    public Animal construct() {
        return new Sheep(world);
    }
}