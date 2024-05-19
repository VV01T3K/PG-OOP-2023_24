package Simulator.Organisms;

import Simulator.Tile;
import Simulator.World;
import Simulator.Organisms.Animals.*;
import Simulator.Organisms.Plants.*;

import org.json.JSONObject;

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
        ANTELOPE("🦌"),
        // CYBER_SHEEP("🤖"),
        FOX("🦊"),
        HUMAN("👨"),
        SHEEP("🐑"),
        TURTLE("🐢"),
        WOLF("🐺"),
        GRASS("🌿"),
        GUARANA("🍅"),
        MILKWEED("🌾"),
        SOSNOWSKY_HOGWEED("🍁"),
        WOLF_BERRIES("🍇");

        private final String symbol;

        Type(String symbol) {
            this.symbol = symbol;
        }

        public String getSymbol() {
            return symbol;
        }

        public static Type getTypeByInt(int i) {
            return Type.values()[i];
        }

        public Organism construct(World w) {
            switch (this) {
                case ANTELOPE:
                    return new Antelope(w);
                case FOX:
                    return new Fox(w);
                case HUMAN:
                    return new Human(w);
                case SHEEP:
                    return new Sheep(w);
                case TURTLE:
                    return new Turtle(w);
                case WOLF:
                    return new Wolf(w);
                case GRASS:
                    return new Grass(w);
                case GUARANA:
                    return new Guarana(w);
                case MILKWEED:
                    return new Milkweed(w);
                case SOSNOWSKY_HOGWEED:
                    return new SosnowskyHogweed(w);
                case WOLF_BERRIES:
                    return new WolfBerries(w);
                default:
                    throw new IllegalStateException("Unexpected value: " + this);
            }
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

    public Organism(JSONObject json, World world) {
        this.type = Type.getTypeByInt(json.getInt("type"));
        this.power = json.getInt("power");
        this.initiative = json.getInt("initiative");
        this.age = json.getLong("age");
        this.alive = json.getBoolean("alive");
        this.reproductionCooldown = json.getInt("reproduction_cooldown");
        this.skip = json.getBoolean("skip");
        this.world = world;
        this.tile = world.getTile(json.getInt("tile_index"));
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

    public JSONObject toJson() {
        JSONObject json = new JSONObject();
        json.put("type", this.type.ordinal());
        json.put("power", this.power);
        json.put("initiative", this.initiative);
        json.put("age", this.age);
        json.put("alive", this.alive);
        json.put("reproduction_cooldown", this.reproductionCooldown);
        json.put("skip", this.skip);
        json.put("tile_index", this.tile.index);
        return json;
    }

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