
from Simulator.World import World
import tkinter as tk
from tkinter import ttk

from Utils.GUI.GUI import GUI
import os


def main():
    world = World(10, 10)
    world.populateWorld()
    world.simulate()
    os.system('cls')
    world.printWorld()
    gui = GUI(world)
    gui.root.mainloop()


if __name__ == "__main__":
    main()
