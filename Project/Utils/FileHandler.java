package Utils;

import org.json.*;

import Simulator.World;
import Simulator.Organisms.Organism;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class FileHandler {
    public static JSONObject readJsonFile(String path) {
        try {
            String content = new String(Files.readAllBytes(Paths.get(path)));
            return new JSONObject(content);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String readFile(String path) {
        try {
            FileReader reader = new FileReader(path);
            StringBuilder content = new StringBuilder();
            int i;
            while ((i = reader.read()) != -1) {
                content.append((char) i);
            }
            reader.close();
            return content.toString();
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void saveWorld(World world) {
        // Assuming World class and its methods are defined elsewhere
        JSONObject json = new JSONObject();
        JSONArray jsonOrganisms = new JSONArray();

        List<Organism> organisms = world.getOrganisms();
        if (organisms.isEmpty())
            return;
        for (Organism organism : organisms) {
            jsonOrganisms.put(organism.toJson());
        }

        JSONObject jsonWorld = new JSONObject();
        jsonWorld.put("width", world.getWidth());
        jsonWorld.put("height", world.getHeight());
        jsonWorld.put("time", world.checkTime());
        jsonWorld.put("hexagonal", world.isHex());

        json.put("organisms", jsonOrganisms);
        json.put("world", jsonWorld);

        try (FileWriter file = new FileWriter("Project\\Saves\\world.json")) {
            file.write(json.toString(2)); // Indent with 2 spaces for readability
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}