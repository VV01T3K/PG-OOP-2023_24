
import sys
import tkinter.messagebox as messagebox
from Simulator.World import World
import tkinter as tk
from tkinter import ttk
from tkinter import simpledialog
from .KeyBindings import KeyBindings


class GUI:
    def __init__(self, world):
        self.world = world
        self.root = tk.Tk()
        self.root.title("Toolbar Example")
        self.root.geometry("800x600")
        self.root.resizable(False, False)
        self.saveToolBar = None
        self.toolbar = self.buildToolBar()
        self.menu = self.buildMenu()
        self.form = self.buildForm()

        self.keyBindings = KeyBindings(self.root)

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

        larger_font = ('Helvetica', 14)

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
        world_type.set("Square")
        world_type_dropdown = tk.OptionMenu(
            form_frame, world_type, "Square", "Hexagonal")
        world_type_dropdown.config(font=larger_font)
        world_type_dropdown.grid(row=2, column=1, padx=10, pady=10, sticky='w')

        def validate_input():
            width = width_entry.get()
            height = height_entry.get()
            world = world_type.get()

            if not width.isdigit() or not height.isdigit() or int(width) <= 1 or int(height) <= 1 or int(width) > 40 or int(height) > 40:
                messagebox.showerror(
                    "Invalid input", "Width and height must be positive integers between 1 and 40.")
                width_entry.delete(0, 'end')
                height_entry.delete(0, 'end')
                return False
            if world not in ["Square", "Hexagonal"]:
                messagebox.showerror(
                    "Invalid input", "World type must be either 'Square' or 'Hexagonal'.")
                world_type.set("Square")
                return False
            return True

        def submit():
            if validate_input():
                self.create_world(width_entry.get(),
                                  height_entry.get(), world_type.get())

        submit_button = tk.Button(
            form_frame, text="Submit", font=larger_font, command=submit)
        submit_button.grid(row=3, column=0, columnspan=4, padx=10, pady=20)

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

        self.showExtendedToolBar()
        self.form.pack(pady=100)

    def buildToolBar(self):
        toolbar = tk.Frame(self.root, bd=1, relief=tk.RAISED)

        menu = tk.Button(toolbar, text="Menu",
                         relief=tk.FLAT, command=self.showMenu)
        menu.pack(side=tk.LEFT, padx=2, pady=2)

        save = tk.Button(toolbar, text="Save",
                         relief=tk.FLAT, command=self.savePopUp)
        save.pack(side=tk.LEFT, padx=2, pady=2)
        self.saveToolBar = save

        return toolbar

    def savePopUp(self):
        filename = simpledialog.askstring("Save game", "Enter filename")
        if filename:
            # self.save_game(filename)
            pass

    def showToolBar(self):
        self.saveToolBar.pack_forget()
        self.toolbar.pack(side=tk.TOP, fill=tk.X)

    def hideToolBar(self):
        self.toolbar.pack_forget()

    def showExtendedToolBar(self):
        self.saveToolBar.pack(side=tk.LEFT, padx=2, pady=2)
        self.toolbar.pack(side=tk.TOP, fill=tk.X)
