package Utils;

import Simulator.World;
import java.io.IOException; // Import statement added for IOException

public class Display {

    private World world;

    public Display(World world) {
        this.world = world;
    }

    public void gameView() {
        try {
            new ProcessBuilder("bash", "-c", "clear").inheritIO().start().waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        for (int y = 0; y < world.getHeight(); y++) {
            for (int x = 0; x < world.getWidth(); x++) {
                System.out.print(world.getTile(x, y));
            }
            System.out.println();
        }
    }

}