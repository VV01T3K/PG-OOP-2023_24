package Simulator.Organisms.Plants;

import Simulator.Organisms.Organism;
import Simulator.World;
import Simulator.GlobalSettings;
import Utils.RNG;
import Simulator.Tile;

public abstract class Plant extends Organism {

    private int reproduction_cooldown = 5;

    public Plant(int power, World world, Type type) {
        super(type, power, 0, world);
    }

    @Override
    public void action() {
        if (!GlobalSettings.AI_REPRODUCE)
            return; // Fixed: Directly access static variable
        if (RNG.getInstance().roll(0, 100) < 5) { // Fixed: Use getInstance() for non-static method access// Fixed:
            Tile newtile = tile.getRandomFreeNeighbour(); // Fixed: Use Java object references, not pointers
            if (newtile == null)
                return; // Fixed: Use null for no object in Java
            Plant newPlant = construct(); // Fixed: Use Java object references, not pointers
            newPlant.skipTurn(); // Fixed: Correct method call syntax
            world.addOrganism(newPlant, newtile);
            // this.setSpreadCooldown(5); // Uncomment if needed
            // newPlant.setSpreadCooldown(5); // Uncomment if needed

            world.addLog(getSymbol() + " is spreading!!");
        }
    }

    @Override
    public void collision(Organism other) {
        // Default implementation does nothing
    }

    @Override
    public boolean collisionReaction(Organism other) {
        return false; // Default implementation does nothing
    }

    public void setSpreadCooldown(int cooldown) {
        this.reproduction_cooldown = cooldown;
    }

    public int getSpreadCooldown() {
        return this.reproduction_cooldown;
    }

    public abstract Plant construct();

}