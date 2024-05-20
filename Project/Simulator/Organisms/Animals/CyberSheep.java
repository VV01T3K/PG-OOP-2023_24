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
        if (target == null) {
            super.action();
            return;
        }
        move(target);
    }

    private int seekClosestSosnowskyHogweed() {
        int index = -1;
        int min_distance = -1;
        for (int i = world.getOrganismCount(); i-- > 0;) { // Fixed iteration direction
            Organism target = world.getOrganism(i);
            if (target.getType() == Organism.Type.SOSNOWSKY_HOGWEED) {
                int distance = world.getDistance(tile, target.getTile());
                if (distance < min_distance) {
                    min_distance = distance;
                    index = i;
                }
            }
        }
        return index;
    }

    private Tile nextTileToSosnowskyHogweed(int index) {
        Tile target = world.getOrganism(index).getTile();
        int distance = world.getDistance(tile, target);
        List<Tile> possibleMoves = new ArrayList<>();
        List<Tile> neighbours = tile.getNeighbours();
        for (Tile neighbour : neighbours) {
            if (world.getDistance(neighbour, target) < distance) {
                possibleMoves.add(neighbour);
            }
        }
        if (possibleMoves.isEmpty())
            return null;
        return possibleMoves.get(RNG.roll(0, possibleMoves.size() - 1));
    }
}