package Simulator.Organisms.Animals;

import Simulator.World;
import Simulator.Tile;
import Utils.RNG;
import java.util.List;

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
        List<Tile> neighbours = tile.getNeighbours();
        neighbours.removeIf(neighbour -> !neighbour.isFree() && neighbour.getOrganism().getPower() > this.power);

        Tile target;
        if (neighbours.isEmpty()) {
            target = tile.getRandomFreeNeighbour();
        } else {
            target = neighbours.get(RNG.getInstance().roll(0, neighbours.size() - 1));
        }
        move(target);
    }
}