
import Simulator.World;
// import Simulator.HexWorld;
import Utils.GUI.GUI;

// import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // World world = new World(5, 5, false);
        // HexWorld world = new HexWorld(20, 20, true);
        // world.populateWorld();
        // Scanner scanner = new Scanner(System.in); // Create a Scanner object

        World world = new World();
        // Display display = new Display(world);
        GUI gui = new GUI(world);
        gui.run();

        // boolean end_flag = false;
        // while (!end_flag) {
        // world.simulate();
        // display.gameView();
        // gui.updateGameView();
        // System.out.println("Press Enter to continue...");
        // String input = scanner.nextLine(); // Wait for the user to press Enter
        // if ("q".equals(input))
        // end_flag = true;
        // }

        // scanner.close();

    }
}