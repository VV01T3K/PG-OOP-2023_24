import Simulator.World;
import Utils.Controller;
import Utils.Display;

public class Main {
    public static void main(String[] args) {
        World world = new World();
        Display display = new Display(world);
        // Controller controller = new Controller(world, display);

        boolean endFlag = false;
        // display.menu(endFlag);
        while (true) {
            if (endFlag)
                break;
            // if (controller.input())
            // display.menu(endFlag);
            world.simulate();
            display.gameView();
        }
    }
}