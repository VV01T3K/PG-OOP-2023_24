package Simulator.Organisms.Plants;

import org.json.JSONObject;

import Simulator.World;

public class Milkweed extends Plant {

    public Milkweed(World world) {
        super(0, world, Type.MILKWEED);
    }

    public Milkweed(JSONObject json, World world) {
        super(json, world);
    }

    @Override
    public Plant construct() {
        return new Milkweed(world);
    }

    @Override
    public void action() {
        super.action();
        super.action();
        super.action();
    }
}