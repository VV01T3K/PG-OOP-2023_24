package Simulator.Organisms.Plants;

import Simulator.Organisms.Organism;
import Simulator.World;
import Simulator.GlobalSettings;
import Utils.RNG;
import Simulator.Tile;

import org.json.JSONObject;

public abstract class Plant extends Organism {

    private int reproduction_cooldown = 5;

    public Plant(int power, World world, Type type) {
        super(type, power, 0, world);
    }

    public Plant(JSONObject json, World world) {
        super(json, world);
    }

    @Override
    public void action() {
        if (!GlobalSettings.AI_REPRODUCE)
            return;
        if (RNG.roll(0, 100) < 5) {
            Tile newtile = tile.getRandomFreeNeighbour();
            if (newtile == null)
                return;
            Plant newPlant = construct();
            newPlant.skipTurn();
            world.addOrganism(newPlant, newtile);
            // this.setSpreadCooldown(5);
            // newPlant.setSpreadCooldown(5);

            world.addLog(getSymbol() + " is spreading!!");
        }
    }

    @Override
    public void collision(Organism other) {
    }

    @Override
    public boolean collisionReaction(Organism other) {
        return false;
    }

    public void setSpreadCooldown(int cooldown) {
        this.reproduction_cooldown = cooldown;
    }

    public int getSpreadCooldown() {
        return this.reproduction_cooldown;
    }

    public abstract Plant construct();

}