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
import java.util.ArrayList;
import java.nio.file.Path;
import java.nio.file.DirectoryStream;
import java.nio.file.DirectoryIteratorException;

public class FileHandler {
    public static void saveWorld(World world, String name, int windowWidth, int windowHeight) {
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
        jsonWorld.put("window_width", windowWidth);
        jsonWorld.put("window_height", windowHeight);

        json.put("organisms", jsonOrganisms);
        json.put("world", jsonWorld);

        try (FileWriter file = new FileWriter("Project/Saves/" + name + ".json")) {
            file.write(json.toString(2)); // Indent with 2 spaces for readability
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static List<String> listSaves() {
        List<String> files = new ArrayList<>();
        Path dir = Paths.get("Project/Saves/");
        try (DirectoryStream<Path> stream = Files.newDirectoryStream(dir, "*.json")) {
            for (Path entry : stream) {
                String filename = entry.getFileName().toString();
                files.add(filename.substring(0, filename.length() - 5));
            }
        } catch (IOException | DirectoryIteratorException e) {
            e.printStackTrace();
        }
        return files;
    }

    public static class WorldLoadResult {
        public final World world;
        public final int windowWidth;
        public final int windowHeight;

        public WorldLoadResult(World world, int windowWidth, int windowHeight) {
            this.world = world;
            this.windowWidth = windowWidth;
            this.windowHeight = windowHeight;
        }
    }

    public static WorldLoadResult loadWorld(String name) {
        try (FileReader file = new FileReader("Project/Saves/" + name + ".json")) {
            JSONObject json = new JSONObject(new JSONTokener(file));
            JSONObject worldJson = json.getJSONObject("world");
            int width = worldJson.getInt("width");
            int height = worldJson.getInt("height");
            long time = worldJson.getLong("time");
            boolean hexagonal = worldJson.optBoolean("hexagonal", false);
            int windowWidth = worldJson.optInt("window_width", 800);
            int windowHeight = worldJson.optInt("window_height", 600);

            World world = new World(width, height, hexagonal);
            world.setTime(time);

            JSONArray jsonOrganisms = json.getJSONArray("organisms");
            List<Organism> organisms = new ArrayList<>();
            OrganismFactory factory = new OrganismFactory();
            for (int i = 0; i < jsonOrganisms.length(); i++) {
                JSONObject organismJson = jsonOrganisms.getJSONObject(i);
                Organism organism = factory.create(organismJson, world);
                organisms.add(organism);
            }
            world.setOrganisms(organisms);
            world.setHuman(world.findHuman());

            return new WorldLoadResult(world, windowWidth, windowHeight);
        } catch (IOException | JSONException e) {
            e.printStackTrace();
        }
        return null;
    }

}