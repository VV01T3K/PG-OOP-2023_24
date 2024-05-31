package Simulator.Organisms.Animals;

import Simulator.Organisms.Organism;
import Utils.RNG;
import Simulator.World;
import Simulator.Tile;
import java.util.List;
import java.util.ArrayList;

import org.json.JSONObject;

public class Antelope extends Animal {

    public Antelope(World world) {
        super(4, 4, world, Type.ANTELOPE);
    }

    public Antelope(JSONObject json, World world) {
        super(json, world);
    }

    @Override

    public Animal construct() {
        return new Antelope(world);
    }

    @Override
    public void action() {
        super.action();
        if (tile.getOrganismCount() > 1)
            if (tile.getOrganism().isAlive())
                return;
        List<Tile> neighbours = new ArrayList<>(tile.getNeighbours());
        neighbours.remove(oldTile);
        if (neighbours.isEmpty())
            return;
        Tile newTile = neighbours.get(RNG.roll(0, neighbours.size() - 1));
        move(newTile);
    }

    @Override
    public void collision(Organism other) {
        if (other instanceof Antelope)
            super.collision(other);
        else if (RNG.roll(0, 100) < 50) {
            Tile newTile = tile.getRandomFreeNeighbour();
            if (newTile == null) {
                super.collision(other);
                return;
            }
            move(newTile);
            world.addLog(getSymbol() + " escaped from " + other.getSymbol() + "!");
        } else
            super.collision(other);
    }

    @Override
    public boolean collisionReaction(Organism other) {
        if (other instanceof Antelope)
            return false;
        if (RNG.roll(0, 100) < 50) {
            Tile newTile = tile.getRandomFreeNeighbour();
            if (newTile == null)
                return false;
            move(newTile);
            return true;
        }
        return false;
    }
}