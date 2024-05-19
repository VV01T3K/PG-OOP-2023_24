package Simulator.Organisms.Plants;

import Simulator.World;
import Simulator.Organisms.Organism;
import Simulator.Tile;

import java.util.ArrayList;

import org.json.JSONObject;

public class SosnowskyHogweed extends Plant {
    public SosnowskyHogweed(World world) {
        super(10, world, Type.SOSNOWSKY_HOGWEED);
    }

    public SosnowskyHogweed(JSONObject json, World world) {
        super(json, world);
    }

    @Override
    public Plant construct() {
        return new SosnowskyHogweed(world);
    }

    @Override
    public void action() {
        super.action();
        ArrayList<String> killed = new ArrayList<>();
        for (Tile neighbour : tile.getOccupiedNeighbours()) {
            Organism organism = neighbour.getOrganism();
            if (organism instanceof Plant)
                continue;
            // if (organism.getType() == Type.CYBER_SHEEP)
            // continue;

            organism.die();
            if (organism.isDead()) {
                killed.add(organism.getSymbol());
            }
        }
        if (!killed.isEmpty()) {
            StringBuilder log = new StringBuilder(getSymbol() + " killed ");
            for (int i = 0; i < killed.size(); i++) {
                log.append(killed.get(i));
                if (i != killed.size() - 1)
                    log.append(", ");
            }
            world.addLog(log.toString() + "!");
            killed.clear();
        }
    }

    @Override
    public boolean collisionReaction(Organism other) {
        if (other instanceof Plant)
            return false;
        // if (other.getType() == Type.CYBER_SHEEP)
        // return false;
        other.die();
        die();
        world.addLog(other.getSymbol() + " ate " + getSymbol() + " and died!");
        return true;
    }
}