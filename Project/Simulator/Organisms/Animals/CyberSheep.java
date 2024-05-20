package Simulator.Organisms.Animals;

import org.json.JSONObject;

import Simulator.World;
import Simulator.Tile;
import Simulator.Organisms.Organism;
import Utils.RNG;

import java.util.ArrayList;
import java.util.List;

public class CyberSheep extends Animal {
    public CyberSheep(World world) {
        super(11, 4, world, Type.CYBER_SHEEP);
    }

    public CyberSheep(JSONObject json, World world) {
        super(json, world);
    }

    @Override
    public Animal construct() {
        return new CyberSheep(world);
    }

    @Override
    public void action() {
        int index = seekClosestSosnowskyHogweed();
        if (index == -1) {
            super.action();
            return;
        }
        Tile target = nextTileToSosnowskyHogweed(index);
        move(target);
        // if (target == null) {
        // super.action();
        // return;
        // }
        // move(target);
    }

    private int seekClosestSosnowskyHogweed() {
        int index = -1;
        int min_distance = -1;
        for (Organism organism : world.getOrganisms()) {
            if (organism.getType() == Type.SOSNOWSKY_HOGWEED) {
                int distance = world.getDistance(tile, organism.getTile());
                if (min_distance == -1 || distance < min_distance) {
                    min_distance = distance;
                    index = world.getOrganisms().indexOf(organism);
                }
            }
        }
        return index;
    }

    private Tile nextTileToSosnowskyHogweed(int index) {
        Tile target = world.getOrganism(index).getTile();
        int distance = world.getDistance(tile, target);
        List<Tile> neighbours = tile.getNeighbours();
        List<Tile> valid = new ArrayList<>();
        for (Tile neighbour : neighbours) {
            if (neighbour == null) {
                continue;
            }
            if (world.getDistance(neighbour, target) < distance) {
                valid.add(neighbour);
            }
        }
        if (valid.isEmpty()) {
            return null;
        }
        target = valid.get(RNG.roll(0, valid.size() - 1));

        return target;
    }
}