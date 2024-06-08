
from Simulator.World import World, HexWorld
from Utils.GUI.GUI import GUI
import os

def main():
    world = HexWorld(10,10)
    world.populateWorld()
    world.simulate()
    os.system('cls')
    gui = GUI(world)
    gui.root.mainloop()

if __name__ == "__main__":
    main()
