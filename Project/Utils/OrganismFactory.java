package Utils;

import org.json.JSONObject; // Corrected import for JSON handling
import java.util.InvalidPropertiesFormatException; // Corrected import for exception handling

import Simulator.World;
import Simulator.Organisms.Organism;
import Simulator.Organisms.Animals.*;
import Simulator.Organisms.Plants.*;

import Simulator.Organisms.Organism.Type;

public class OrganismFactory {

    public Organism create(JSONObject json, World world) throws InvalidPropertiesFormatException {

        Type type = Organism.Type.getTypeByInt(json.getInt("type"));

        switch (type) {
            case ANTELOPE:
                return new Antelope(json, world);
            case FOX:
                return new Fox(json, world);
            case HUMAN:
                return new Human(json, world);
            case SHEEP:
            case CYBER_SHEEP:
                return new Sheep(json, world);
            case TURTLE:
                return new Turtle(json, world);
            case WOLF:
                return new Wolf(json, world);
            case GRASS:
                return new Grass(json, world);
            case GUARANA:
                return new Guarana(json, world);
            case MILKWEED:
                return new Milkweed(json, world);
            case SOSNOWSKY_HOGWEED:
                return new SosnowskyHogweed(json, world);
            case WOLF_BERRIES:
                return new WolfBerries(json, world);
            default:
                throw new InvalidPropertiesFormatException("Invalid type");
        }
    }
}