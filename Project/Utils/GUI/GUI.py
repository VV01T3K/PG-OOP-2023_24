
import sys
from Simulator.World import World
import tkinter as tk
from tkinter import ttk


class GUI:
    def __init__(self, world):
        self.world = world
        self.root = tk.Tk()
        self.root.title("Toolbar Example")
        self.root.geometry("800x600")
        self.root.resizable(False, False)
        self.toolbar = self.buildToolBar()
        self.menu = self.buildMenu()
        self.form = self.buildForm()

        self.showMenu()

    def buildMenu(self):
        def continueGame():
            print("Continue the game")

        def startGame():
            self.showForm()

        def loadGame():
            print("Load game")

        def exitGame():
            self.root.destroy()
            sys.exit()

        menu_frame = tk.Frame(self.root)

        continue_button = tk.Button(menu_frame, text="Continue the game",
                                    relief=tk.FLAT, command=continueGame, height=2, width=20,
                                    background='gray', foreground='black', font=("Helvetica", 16))
        start_button = tk.Button(menu_frame, text="Start new game",
                                 relief=tk.FLAT, command=startGame, height=2, width=20,
                                 background='gray', foreground='black', font=("Helvetica", 16))
        load_button = tk.Button(menu_frame, text="Load game",
                                relief=tk.FLAT, command=loadGame, height=2, width=20,
                                background='gray', foreground='black', font=("Helvetica", 16))
        exit_button = tk.Button(menu_frame, text="Exit",
                                relief=tk.FLAT, command=exitGame, height=2, width=20,
                                background='red', foreground='white', font=("Helvetica", 16))

        continue_button.pack(pady=10)
        start_button.pack(pady=10)
        load_button.pack(pady=10)
        exit_button.pack(pady=10)

        menu_frame.pack(pady=100)

        return menu_frame

    def buildForm(self):
        root = self.root
        form_frame = tk.Frame(root)

        # Define a larger font
        larger_font = ('Arial', 14)

        width_label = tk.Label(form_frame, text="Width:", font=larger_font)
        width_label.grid(row=0, column=0, padx=10, pady=10, sticky='w')
        width_entry = tk.Entry(form_frame, font=larger_font)
        width_entry.grid(row=0, column=1, padx=10, pady=10, sticky='w')

        height_label = tk.Label(form_frame, text="Height:", font=larger_font)
        height_label.grid(row=1, column=0, padx=10, pady=10, sticky='w')
        height_entry = tk.Entry(form_frame, font=larger_font)
        height_entry.grid(row=1, column=1, padx=10, pady=10, sticky='w')

        world_type_label = tk.Label(
            form_frame, text="World Type:", font=larger_font)
        world_type_label.grid(row=2, column=0, padx=10, pady=10, sticky='w')
        world_type = tk.StringVar(root)
        world_type.set("Square")  # default value
        world_type_dropdown = tk.OptionMenu(
            form_frame, world_type, "Square", "Hexagonal")
        # For dropdown, use config method
        world_type_dropdown.config(font=larger_font)
        world_type_dropdown.grid(row=2, column=1, padx=10, pady=10, sticky='w')

        submit_button = tk.Button(form_frame, text="Submit", font=larger_font, command=lambda: self.create_world(
            width_entry.get(), height_entry.get(), world_type.get()))
        submit_button.grid(row=3, column=0, columnspan=4,
                           padx=10, pady=20)

        return form_frame

    def create_world(self, width, height, world_type):
        # Here you can add the logic to create a new world with the given width, height, and world type
        print(
            f"Creating a new {world_type} world with width {width} and height {height}")

    def showMenu(self):
        self.form.pack_forget()

        self.hideToolBar()
        self.menu.pack(pady=100)

    def showForm(self):
        self.menu.pack_forget()

        self.showToolBar()
        self.form.pack(pady=100)

    def buildToolBar(self):
        toolbar = tk.Frame(self.root, bd=1, relief=tk.RAISED)

        button_one = tk.Button(toolbar, text="Menu",
                               relief=tk.FLAT, command=self.showMenu)
        button_one.pack(side=tk.LEFT, padx=2, pady=2)

        # button_two = tk.Button(toolbar, text="Hide toolbar",
        #                        relief=tk.FLAT, command=self.toggleToolBar)
        # button_two.pack(side=tk.LEFT, padx=2, pady=2)
        return toolbar

    def showToolBar(self):
        self.toolbar.pack(side=tk.TOP, fill=tk.X)

    def hideToolBar(self):
        self.toolbar.pack_forget()

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
