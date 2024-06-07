
from Simulator.World import World
import tkinter as tk
from tkinter import ttk

from Utils.GUI.GUI import GUI


def main():
    world = World(5, 5)
    gui = GUI(world)
    gui.squareKeyBindings()
    gui.root.mainloop()


if __name__ == "__main__":
    main()
