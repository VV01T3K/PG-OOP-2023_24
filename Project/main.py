
from Simulator.World import World
from Utils.GUI.GUI import GUI
import os


def main():
    world = World(10, 10)
    world.populateWorld()
    world.simulate()
    os.system('cls')
    world.printWorld()
    world.addLog("Test")
    world.addLog("Test")
    world.addLog("Test")
    world.addLog("Test")
    world.addLog("Test")
    gui = GUI(world)
    gui.root.mainloop()


if __name__ == "__main__":
    main()
