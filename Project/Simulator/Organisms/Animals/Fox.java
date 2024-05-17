package Simulator.Organisms.Animals;

import Simulator.World;
import Simulator.Tile;
import Utils.RNG;
import java.util.List;
import java.util.ArrayList;

public class Fox extends Animal {

    public Fox(World world) {
        super(3, 7, world, Type.FOX);
    }

    @Override
    public Animal construct() {
        return new Fox(world);
    }

    @Override
    public void action() {
        List<Tile> neighbours = new ArrayList<>(tile.getNeighbours()); // Use a new list to avoid
                                                                       // ConcurrentModificationException
        neighbours.removeIf(neighbour -> neighbour == null || !neighbour.isFree()
                || (neighbour.getOrganism() != null && neighbour.getOrganism().getPower() > this.power));

        Tile target;
        if (neighbours.isEmpty()) {
            target = tile.getRandomFreeNeighbour();
        } else {
            target = neighbours.get(RNG.getInstance().roll(0, neighbours.size() - 1));
        }
        move(target);
    }
}