
import sys
import tkinter.messagebox as messagebox
from Simulator.World import World
from Simulator.Organisms.Organism import Type
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
        self.saveToolBar = None
        self.toolbar = self.buildToolBar()
        self.continueButton = None
        self.menu = self.buildMenu()
        self.form = self.buildForm()
        self.buildSquareWorldPanel()

        self.keyBindings = KeyBindings(self.root)

        self.showMenu()

    def getActiveWorld(self):
        return self.world

    def buildMenu(self):
        def continueGame():
            self.showGameView()

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

        self.continueButton = continue_button

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

    def resetFrames(self):
        self.menu.pack_forget()
        self.form.pack_forget()
        self.squareWorldPanelFrame.pack_forget()
        self.hideToolBar()

    def showMenu(self):
        self.resetFrames()
        if (not self.getActiveWorld() == None and self.getActiveWorld().checkTime() > 0):
            self.continueButton.pack(pady=10)
        else:
            self.continueButton.pack_forget()
        self.menu.pack(pady=100)

    def showForm(self):
        self.resetFrames()
        self.showToolBar()
        self.form.pack(pady=100)

    def showToolBar(self):
        self.toolbar.pack(side=tk.TOP, fill=tk.X)

    def showExtendedToolBar(self):
        self.saveToolBar.pack(side=tk.LEFT, padx=2, pady=2)
        self.toolbar.pack(side=tk.TOP, fill=tk.X)

    def showGameView(self):
        self.resetFrames()
        self.showExtendedToolBar()
        self.squareWorldPanelFrame.pack(expand=True)

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

    def hideToolBar(self):
        self.toolbar.pack_forget()

    def buildSquareWorldPanel(self):
        width = self.getActiveWorld().getWidth()
        height = self.getActiveWorld().getHeight()
        # Create a new frame for the game board
        self.squareWorldPanelFrame = tk.Frame(self.root)

        # Create a dictionary to store the buttons
        self.buttons = {}

        # Create the buttons
        for x in range(width):
            for y in range(height):
                button = tk.Button(
                    self.squareWorldPanelFrame, text=f'({x},{y})', font=("default", 20))
                button.grid(row=y, column=x)

                # Store the button in the dictionary
                self.buttons[(x, y)] = button

                # Add a click event to the button
                button.bind("<Button-1>", lambda e, x=x,
                            y=y: self.useAddOrganismPopup(x, y, button))
        self.updateButtonsText()

    def updateButtonsText(self):
        for x in range(self.getActiveWorld().getWidth()):
            for y in range(self.getActiveWorld().getHeight()):
                button = self.buttons[(x, y)]
                symbol = f'{self.getActiveWorld().getTile(x, y)}'
                if (symbol == "🔳"):
                    symbol = "    "
                button.config(text=symbol)

    def useAddOrganismPopup(self, x, y, button):
        # Create a new context menu
        addOrganismPopup = tk.Menu(self.root, tearoff=0)

        # Get the type of the organism on the button
        button_type = button.cget('text')

        # If the organism is a human and there is already a human in the world, return
        if button_type == Type.HUMAN and self.world.hasHuman():
            return

        # For each type of organism
        for type in Type:
            # If the type is a human and there is already a human in the world, skip this iteration
            if type == Type.HUMAN and self.world.hasHuman():
                continue

            # Create a new menu item for the organism
            addOrganismPopup.add_command(label=f'{type}',
                                         command=lambda type=type: self.addOrganismAndShowGameView(type, x, y))

        # Show the context menu at the position of the button
        addOrganismPopup.tk_popup(button.winfo_rootx(), button.winfo_rooty())

    def addOrganismAndShowGameView(self, type, x, y):
        pass

    # def hexWorldPanel(self):
    #     self.hexWorldPanelFrame.pack(pady=100)

    # def buildcontrolPanel(self):
    #     self.controlPanelFrame.pack(pady=100)
