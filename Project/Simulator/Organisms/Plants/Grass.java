package Simulator.Organisms.Plants;

import org.json.JSONObject;

import Simulator.World;

public class Grass extends Plant {
    public Grass(World world) {
        super(0, world, Type.GRASS);
    }

    public Grass(JSONObject json, World world) {
        super(json, world);
    }

    @Override
    public Plant construct() {
        return new Grass(world);
    }

}