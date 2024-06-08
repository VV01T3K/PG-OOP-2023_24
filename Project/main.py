
from Simulator.World import World
from Utils.GUI.GUI import GUI
import os


def main():
    world = World()
    os.system('cls')
    gui = GUI(world)
    gui.root.mainloop()


if __name__ == "__main__":
    main()
