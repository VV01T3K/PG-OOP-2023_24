package Simulator.Organisms;

import Simulator.Tile;
import Simulator.World;

public abstract class Organism {
    protected int power;
    protected int initiative;
    protected long age = 0;
    protected boolean alive = true;
    protected int reproductionCooldown;
    protected boolean skip = false;
    protected Tile tile = null;
    protected World world;
    protected Type type;

    public enum Type {
        // ANTELOPE("🦌"),
        // CYBER_SHEEP("🤖"),
        // FOX("🦊"),
        // HUMAN("👨"),
        // SHEEP("🐑"),
        // TURTLE("🐢"),
        // WOLF("🐺"),
        // GRASS("🌿"),
        // GUARANA("🍅"),
        // MILKWEED("🌾"),
        // SOSNOWSKY_HOGWEED("🍁"),
        // WOLF_BERRIES("🍇");
        ANTELOPE("A"),
        CYBER_SHEEP("C"),
        FOX("F"),
        HUMAN("H"),
        SHEEP("S"),
        TURTLE("T"),
        WOLF("W"),
        GRASS("G"),
        GUARANA("G"),
        MILKWEED("M"),
        SOSNOWSKY_HOGWEED("S"),
        WOLF_BERRIES("W");

        private final String symbol;

        Type(String symbol) {
            this.symbol = symbol;
        }

        public String getSymbol() {
            return symbol;
        }
    }

    public Type getType() {
        return type;
    }

    public Organism(Type type, int power, int initiative, World world) {
        this.type = type;
        this.power = power;
        this.initiative = initiative;
        this.world = world;
    }

    public Tile getTile() {
        return tile;
    }

    public void setTile(Tile tile) {
        this.tile = tile;
    }

    public void age() {
        if (reproductionCooldown > 0)
            reproductionCooldown--;
        age++;
    }

    public void setBreedCooldown(int turns) {
        this.reproductionCooldown = turns;
    }

    public void die() {
        alive = false;
    }

    public boolean isDead() {
        return !alive;
    }

    public boolean isAlive() {
        return alive;
    }

    public void skipTurn() {
        skip = true;
    }

    public void unskipTurn() {
        skip = false;
    }

    public boolean isSkipped() {
        return skip;
    }

    public int getPower() {
        return power;
    }

    public int getInitiative() {
        return initiative;
    }

    public long getAge() {
        return age;
    }

    public void setPower(int power) {
        this.power = power;
    }

    public void setInitiative(int initiative) {
        this.initiative = initiative;
    }

    public String getSymbol() {
        return type.getSymbol();
    }

    public void draw() {
        System.out.println(getSymbol());
    }

    public abstract void action();

    public abstract void collision(Organism other);

    public abstract boolean collisionReaction(Organism other);

    public abstract Organism construct();

    // public Map<String, Object> toJson() {
    // ObjectMapper mapper = new ObjectMapper();
    // Map<String, Object> json = mapper.convertValue(this, Map.class);
    // return json;
    // }

    // public Organism(Map<String, Object> json, World world) {
    // // Assuming ObjectMapper can handle this conversion. You might need to
    // manually
    // // parse fields.
    // ObjectMapper mapper = new ObjectMapper();
    // Organism organism = mapper.convertValue(json, Organism.class);
    // this.type = organism.type;
    // this.power = organism.power;
    // this.initiative = organism.initiative;
    // this.age = organism.age;
    // this.alive = organism.alive;
    // this.reproductionCooldown = organism.reproductionCooldown;
    // this.skip = organism.skip;
    // this.tile = organism.tile;
    // this.world = world;
    // }
}