
import Simulator.World;
// import Simulator.HexWorld;
import Utils.Display;

import Utils.GUI;

// import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // World world = new World(20, 20, false);
        // HexWorld world = new HexWorld(20, 20, true);
        // Display display = new Display(world);
        // Scanner scanner = new Scanner(System.in); // Create a Scanner object

        World world = new World(10, 10, false);
        GUI gui = new GUI(world);
        Display display = new Display(world);
        world.populateWorld();
        display.gameView();
        gui.run();
        gui.showMenu();

        // boolean end_flag = false;
        // while (!end_flag) {
        // world.simulate();
        // display.gameView();
        // System.out.println("Press Enter to continue...");
        // String input = scanner.nextLine(); // Wait for the user to press Enter
        // if ("q".equals(input))
        // end_flag = true;
        // }

        // scanner.close();

    }
}