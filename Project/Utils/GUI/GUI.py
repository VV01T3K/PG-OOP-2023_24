
from Simulator.World import World
import tkinter as tk
from tkinter import ttk


class GUI:
    def __init__(self, world: World):
        self.world = world
        self.root = tk.Tk()
        self.root.title("Toolbar Example")
        self.root.geometry("800x600")
        self.root.resizable(False, False)

        # Create a toolbar frame
        toolbar = tk.Frame(self.root, bd=1, relief=tk.RAISED)

        # Add buttons to the toolbar
        button_one = tk.Button(toolbar, text="Button 1", relief=tk.FLAT)
        button_one.pack(side=tk.LEFT, padx=2, pady=2)

        button_two = tk.Button(toolbar, text="Button 2", relief=tk.FLAT)
        button_two.pack(side=tk.LEFT, padx=2, pady=2)

        # Pack the toolbar
        toolbar.pack(side=tk.TOP, fill=tk.X)

        # if toolbar.winfo_viewable():
        #     toolbar.pack_forget()
        # else:
        #     toolbar.pack(side=tk.TOP, fill=tk.X)

    def squareKeyBindings(self):
        root = self.root
        self.resetKeyBindings()

        def moveUp(e):
            print("Move up")

        def moveDown(e):
            print("Move down")

        def moveLeft(e):
            print("Move left")

        def moveRight(e):
            print("Move right")

        def nextRound(e):
            print("Next round")

        root.bind("<space>", nextRound)

        root.bind("w", moveUp)
        root.bind("s", moveDown)
        root.bind("a", moveLeft)
        root.bind("d", moveRight)

        root.bind("<Up>", moveUp)
        root.bind("<Down>", moveDown)
        root.bind("<Left>", moveLeft)
        root.bind("<Right>", moveRight)

    def hexagonalKeyBindings(self):
        root = self.root
        self.resetKeyBindings()

        def moveUp(e):
            print("Move up")

        def moveDown(e):
            print("Move down")

        def moveTopLeft(e):
            print("Move top left")

        def moveBottomLeft(e):
            print("Move bottom left")

        def moveTopRight(e):
            print("Move top right")

        def moveBottomRight(e):
            print("Move bottom right")

        def nextRound(e):
            print("Next round")

        root.bind("<space>", nextRound)

        root.bind("Q", moveTopLeft)
        root.bind("W", moveUp)
        root.bind("E", moveTopRight)
        root.bind("A", moveBottomLeft)
        root.bind("S", moveDown)
        root.bind("D", moveBottomRight)

        root.bind("<KP_Up>", moveUp)
        root.bind("<KP_Down>", moveDown)
        root.bind("<KP_Home>", moveTopLeft)
        root.bind("<KP_Prior>", moveTopRight)
        root.bind("<KP_End>", moveBottomLeft)
        root.bind("<KP_Next>", moveBottomRight)

    def resetKeyBindings(self):
        keys = ["w", "s", "a", "d", "<space>", "<Up>", "<Down>", "<Left>", "<Right>",
                "Q", "W", "E", "A", "S", "D", "<KP_Up>", "<KP_Down>", "<KP_Home>",
                "<KP_Prior>", "<KP_End>", "<KP_Next>"]
        for key in keys:
            self.root.unbind(key)
