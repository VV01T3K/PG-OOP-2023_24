import Simulator.World;
import Utils.Display;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        World world = new World();
        Display display = new Display(world);
        Scanner scanner = new Scanner(System.in); // Create a Scanner object

        boolean end_flag = false;
        while (!end_flag) {
            world.simulate();
            display.gameView();
            System.out.println("Press Enter to continue...");
            String input = scanner.nextLine(); // Wait for the user to press Enter
            if ("q".equals(input))
                end_flag = true;
        }

        scanner.close();

    }
}