package Simulator;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import Simulator.Organisms.Organism;
import Utils.RNG;
import Utils.DynamicDirections;

public class Tile {
    private Tile[] directions;
    private List<Organism> organisms = new ArrayList<>();
    public final int index;

    public Tile(int index, int directionCount) {
        this.index = index;
        directions = new Tile[directionCount];
    }

    @Override
    public String toString() {
        return organisms.isEmpty() ? "" : organisms.get(0).getSymbol();
    }

    public void clear() {
        organisms.clear();
    }

    public void setLink(DynamicDirections direction, Tile tile) {
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
        return freeNeighbours.get(RNG.roll(0, freeNeighbours.size()));
    }

    public Tile getNeighbour(DynamicDirections direction) {
        return directions[direction.ordinal()];
    }

    public Tile getRandomNeighbour() {
        List<Tile> neighbours = Arrays.stream(directions)
                .filter(tile -> tile != null)
                .collect(Collectors.toList());
        if (neighbours.isEmpty())
            return null;
        return neighbours.get(RNG.roll(0, neighbours.size()));
    }

    public DynamicDirections getRandomDirection() {
        List<DynamicDirections> availableDirections = Arrays.stream(directions)
                .filter(tile -> tile != null)
                .map(tile -> DynamicDirections.values()[Arrays.asList(directions).indexOf(tile)])
                .collect(Collectors.toList());
        if (availableDirections.isEmpty())
            return DynamicDirections.get("SELF");
        return availableDirections.get(RNG.roll(0, availableDirections.size()));
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
}