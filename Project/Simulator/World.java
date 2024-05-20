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
    protected List<Organism> organisms;
    protected List<Tile> tiles;
    protected List<String> logs = new ArrayList<>();
    protected Human human = null;

    public World(int width, int height) {
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

    public void setTime(long time) {
        this.time = time;
    }

    public World() {
        this(20, 20);
    }

    public World(boolean hex) {
    }

    protected void createBoard(int width, int height) {
        for (int i = 0; i < width * height; i++) {
            tiles.add(new Tile(i, 4));
        }
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
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

    public int getDistance(Tile tile, Tile target) {
        int x1 = tile.index % width;
        int y1 = tile.index / width;
        int x2 = target.index % width;
        int y2 = target.index / width;
        return Math.abs(x1 - x2) + Math.abs(y1 - y2);
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

        organisms.sort((a, b) -> {
            if (a.getInitiative() == b.getInitiative()) {
                return Long.compare(b.getAge(), a.getAge());
            }
            return Integer.compare(b.getInitiative(), a.getInitiative());
        });

        for (Organism organism : new ArrayList<>(organisms)) {
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
            tiles.set(i, null);
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
        setHuman(human);

        spreadOrganisms(new SosnowskyHogweed(this), 1);
        // spreadOrganisms(new Grass(this), 3);
        // spreadOrganisms(new Guarana(this), 3);
        // spreadOrganisms(new Milkweed(this), 3);
        // spreadOrganisms(new WolfBerries(this), 3);

        // spreadOrganisms(new Wolf(this), 3);
        // spreadOrganisms(new Sheep(this), 1);
        spreadOrganisms(new CyberSheep(this), 1);
        // spreadOrganisms(new Fox(this), 3);
        // spreadOrganisms(new Turtle(this), 3);
        // spreadOrganisms(new Antelope(this), 3);
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