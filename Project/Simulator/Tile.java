package Simulator;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import Simulator.Organisms.Organism;
import Utils.RNG;

public class Tile {
    private Tile[] directions = new Tile[4];
    private List<Organism> organisms = new ArrayList<>();
    public final int index;

    public Tile(int index) {
        this.index = index;
        // In Java, the array is already initialized to null, so no need to fill it with
        // nulls.
        // The ArrayList does not need to be reserved as in C++, it dynamically resizes.
    }

    @Override
    public String toString() {
        return organisms.isEmpty() ? "🔳" : organisms.get(0).getSymbol();
    }

    public void clear() {
        organisms.clear();
    }

    public void setLink(Direction direction, Tile tile) {
        directions[direction.ordinal()] = tile;
    }

    public Organism getOrganism() {
        return organisms.isEmpty() ? null : organisms.get(0);
    }

    public void placeOrganism(Organism organism) {
        organisms.add(organism);
    }

    public void removeOrganism(Organism organism) {
        organisms.remove(organism);
    }

    public Tile getRandomFreeNeighbour() {
        List<Tile> freeNeighbours = Arrays.stream(directions)
                .filter(tile -> tile != null && tile.isFree())
                .collect(Collectors.toList());
        if (freeNeighbours.isEmpty())
            return null;
        return freeNeighbours.get(RNG.getInstance().roll(0, freeNeighbours.size()));
    }

    public Tile getNeighbour(Direction direction) {
        return directions[direction.ordinal()];
    }

    public Tile getRandomNeighbour() {
        List<Tile> neighbours = Arrays.stream(directions)
                .filter(tile -> tile != null)
                .collect(Collectors.toList());
        if (neighbours.isEmpty())
            return null;
        return neighbours.get(RNG.getInstance().roll(0, neighbours.size()));
    }

    public Direction getRandomDirection() {
        List<Direction> availableDirections = Arrays.stream(directions)
                .filter(tile -> tile != null)
                .map(tile -> Direction.values()[Arrays.asList(directions).indexOf(tile)])
                .collect(Collectors.toList());
        if (availableDirections.isEmpty())
            return Direction.SELF;
        return availableDirections.get(RNG.getInstance().roll(0, availableDirections.size()));
    }

    public boolean isFree() {
        return organisms.isEmpty();
    }

    public List<Tile> getNeighbours() {
        return Arrays.asList(directions);
    }

    public List<Tile> getOccupiedNeighbours() {
        return Arrays.stream(directions)
                .filter(tile -> tile != null && !tile.isFree())
                .collect(Collectors.toList());
    }

    public long getOrganismCount() {
        return organisms.size();
    }

    // public long getDistanceTo(Tile tile, long width) {
    // long dx = Math.abs(this.index % width - tile.index % width);
    // long dy = Math.abs(this.index / width - tile.index / width);
    // return dx + dy;
    // }

    public enum Direction {
        UP, DOWN, RIGHT, LEFT, SELF
    }
}