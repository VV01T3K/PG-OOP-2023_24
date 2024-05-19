
import Simulator.World;
import Utils.GUI.GUI;

public class Main {
    public static void main(String[] args) {
        World world = new World();
        GUI gui = new GUI(world);
        gui.run();
    }
}