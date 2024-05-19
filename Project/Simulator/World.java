package Simulator;

import java.util.ArrayList;
import java.util.List;

import Simulator.Organisms.Organism;
import Simulator.Organisms.Animals.*;
import Simulator.Organisms.Plants.*;
import Utils.DynamicDirections;
import Utils.RNG;

public class World {
    protected int width;
    protected int height;
    protected long time = 0;
    protected List<Organism> organisms; // will be sorted by initiative and age
    protected List<Tile> tiles;
    protected List<String> logs = new ArrayList<>();
    protected Human human = null;

    public World(int width, int height, boolean hex) {

        if (hex) {
            return;
        }

        DynamicDirections.clear();

        DynamicDirections.addInstance("UP");
        DynamicDirections.addInstance("RIGHT");
        DynamicDirections.addInstance("DOWN");
        DynamicDirections.addInstance("LEFT");
        DynamicDirections.addInstance("SELF");

        this.width = width;
        this.height = height;
        this.organisms = new ArrayList<>();
        this.tiles = new ArrayList<>();
        this.logs = new ArrayList<>();
        createBoard(width, height);
    }

    public World() {
        this(20, 20, false);
    }

    protected void createBoard(int width, int height) {
        // Initialize tiles based on width and height
        for (int i = 0; i < width * height; i++) {
            tiles.add(new Tile(i, 4));
        }
        // Set links between tiles
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Tile tile = tiles.get(y * width + x);
                if (y > 0) {
                    tile.setLink(DynamicDirections.get("UP"), tiles.get((y - 1) * width + x));
                }
                if (x < width - 1) {
                    tile.setLink(DynamicDirections.get("RIGHT"), tiles.get(y * width + x + 1));
                }
                if (y < height - 1) {
                    tile.setLink(DynamicDirections.get("DOWN"), tiles.get((y + 1) * width + x));
                }
                if (x > 0) {
                    tile.setLink(DynamicDirections.get("LEFT"), tiles.get(y * width + x - 1));
                }
            }
        }
    }

    public long getDistanceTo(Tile tile, Tile target) {
        long dx = Math.abs(tile.index % width - target.index % width);
        long dy = Math.abs(tile.index / width - target.index / width);
        return dx + dy;
    }

    public void setWorld(int width, int height, long time) {
        this.clearTiles();
        this.width = width;
        this.height = height;
        this.time = time;
        createBoard(width, height);
    }

    public long checkTime() {
        return time;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public Tile getTile(int index) {
        return tiles.get(index);
    }

    public Tile getTile(int x, int y) {
        return tiles.get(y * width + x);
    }

    public void setTile(int x, int y, Tile tile) {
        tiles.set(y * width + x, tile);
    }

    public Organism getOrganism(int index) {
        return organisms.get(index);
    }

    public void addOrganism(Organism organism, Tile tile) {
        organisms.add(organism);
        organism.setTile(tile);
        tile.placeOrganism(organism);
    }

    @SuppressWarnings("unused")
    public void simulate() {
        time++;
        clearLogs();

        // Sort organisms based on initiative and age
        organisms.sort((a, b) -> {
            if (a.getInitiative() == b.getInitiative()) {
                // Fixed to handle comparison of long values
                return Long.compare(b.getAge(), a.getAge()); // Note the order is reversed for age
            }
            return Integer.compare(b.getInitiative(), a.getInitiative()); // Higher initiative first
        });

        // Iterate through organisms for actions
        for (Organism organism : new ArrayList<>(organisms)) { // To avoid ConcurrentModificationException
            if (organism.isSkipped() || organism.isDead())
                continue;
            if (!GlobalSettings.AI_ACTION && !(organism instanceof Human))
                continue;

            organism.action();

            if (organism.getTile().getOrganismCount() > 1) {
                Organism other = organism.getTile().getOrganism();
                if (organism.equals(other) || other.isDead())
                    continue;
                organism.collision(other);
            }
        }

        // Handle post-round actions and remove dead organisms
        organisms.removeIf(organism -> {
            if (organism.isDead()) {
                organism.getTile().removeOrganism(organism);
                if (organism instanceof Human)
                    human = null;
                return true;
            }
            organism.age();
            organism.unskipTurn();
            return false;
        });
    }

    public int getOrganismCount() {
        return organisms.size();
    }

    public void spreadOrganisms(Organism organism, int count) {
        int max = width * height - 1;
        while (count > 0 && getOrganismCount() < max) {
            Tile tile = tiles.get(RNG.roll(0, tiles.size() - 1));
            if (tile.isFree()) {
                addOrganism(organism.construct(), tile);
                count--;
            }
        }
    }

    public void linkOrganismsWithTiles() {
        for (Organism organism : organisms) {
            getTile(organism.getTile().index).placeOrganism(organism);
        }
    }

    public List<Organism> getOrganisms() {
        return new ArrayList<>(organisms);
    }

    public void setOrganisms(List<Organism> organisms) {
        this.clearOrganisms();
        this.organisms = new ArrayList<>(organisms);
        linkOrganismsWithTiles();
    }

    public void clearOrganisms() {
        organisms.clear();
        human = null;
    }

    public void clearTiles() {
        for (int i = 0; i < tiles.size(); i++) {
            tiles.set(i, null); // Explicitly setting to null, if necessary
        }
        tiles.clear();
    }

    public void cleanTiles() {
        for (Tile tile : tiles) {
            tile.clear();
        }
    }

    public void resetWorld() {
        clearOrganisms();
        cleanTiles();
        clearLogs();
        time = 0;
    }

    public void populateWorld() {
        resetWorld();

        Human human = new Human(this);
        spreadOrganisms(human, 1);
        setHuman(human); // Assuming setHuman sets the 'human' field in World

        spreadOrganisms(new SosnowskyHogweed(this), 3);
        spreadOrganisms(new Grass(this), 3);
        spreadOrganisms(new Guarana(this), 3);
        spreadOrganisms(new Milkweed(this), 3);
        spreadOrganisms(new WolfBerries(this), 3);

        spreadOrganisms(new Wolf(this), 3);
        spreadOrganisms(new Sheep(this), 3);
        // spreadOrganisms(new CyberSheep(this), 3);
        spreadOrganisms(new Fox(this), 3);
        spreadOrganisms(new Turtle(this), 3);
        spreadOrganisms(new Antelope(this), 3);
    }

    public void addLog(String log) {
        logs.add(log);
    }

    public List<String> getLogs() {
        return logs;
    }

    public void clearLogs() {
        logs.clear();
    }

    public void setHuman(Human human) {
        this.human = human;
    }

    public void setHuman(Organism organism) {
        if (organism instanceof Human) {
            this.human = (Human) organism;
        }
    }

    public Human getHuman() {
        return human;
    }

    public boolean hasHuman() {
        return human != null;
    }

    public Human findHuman() {
        for (Organism organism : organisms) {
            if (organism instanceof Human) {
                return (Human) organism;
            }
        }
        return null;
    }

    public void setNewOrganism(Organism.Type type, int x, int y) {
        Tile tile = getTile(x, y);
        while (!tile.isFree())
            tile.removeOrganism(tile.getOrganism());
        Organism organism = type.construct(this);
        organism.skipTurn();
        addOrganism(organism, tile);
        addLog("New " + type.getSymbol() + " " + type + " spawned!");
    }

}