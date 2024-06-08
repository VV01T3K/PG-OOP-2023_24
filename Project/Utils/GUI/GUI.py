
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
        self.root.geometry("900x600")
        self.saveToolBar = None
        self.toolbar = self.buildToolBar()
        self.continueButton = None
        self.menu = self.buildMenu()
        self.form = self.buildForm()
        self.controlPanel = None
        self.logPanel = None
        self.worldPanel = None
        self.buttons = {}
        self.gameView = None
        self.gameView = self.buildGameView()
        
        self.keyBindings = KeyBindings(self.root)

        self.showMenu()

    def getActiveWorld(self) -> World:
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
        self.hideToolBar()
        self.worldPanel.pack_forget()
        self.logPanel.pack_forget()
        self.controlPanel.pack_forget()
        self.gameView.pack_forget()

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
        self.gameView.pack(fill=tk.BOTH, expand=1)

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

    def buildSquareWorldPanel(self, panel):
        width = self.getActiveWorld().getWidth()
        height = self.getActiveWorld().getHeight()
        squareWorldPanelFrame = tk.Frame(panel)
        self.buttons = {}
        for x in range(width):
            for y in range(height):
                button = tk.Button(
                    squareWorldPanelFrame, text=f'({x},{y})', font=("default", 20), width=3)
                button.grid(row=y, column=x)
                self.buttons[(x, y)] = button
                button.bind("<Button-1>", lambda e, x=x,
                            y=y: self.useAddOrganismPopup(e, x, y))
                button.config(relief=tk.RAISED)
        self.updateButtonsText()
        return squareWorldPanelFrame

    def updateButtonsText(self):
        for x in range(self.getActiveWorld().getWidth()):
            for y in range(self.getActiveWorld().getHeight()):
                self.updateButtonText(x, y)

    def updateButtonText(self, x, y):
        button = self.buttons[(x, y)]
        symbol = f'{self.getActiveWorld().getTile(x, y)}'
        if (symbol == "🔳"):
            symbol = "    "
        button.config(text=symbol)

    def useAddOrganismPopup(self, event, x, y):
        def addOrganism(type, x, y):
            self.getActiveWorld().setNewOrganism(type, x, y)
            if type == Type.HUMAN:
                self.getActiveWorld().setHuman(self.getActiveWorld().findHuman())
                self.getActiveWorld().getHuman().unskipTurn()
            self.updateButtonText(x, y)
            self.updateLogPanel()

        addOrganismPopup = tk.Menu(self.root, tearoff=0)
        button_type = self.getActiveWorld().getTile(x, y).getOrganism()
        if button_type is not None:
            button_type = button_type.getType()
            if button_type == Type.HUMAN and self.getActiveWorld().hasHuman():
                return
        for type in Type:
            if type == Type.HUMAN and self.getActiveWorld().hasHuman():
                continue
            addOrganismPopup.add_command(label=f'{type.getSymbol()} - {type.getName()}',
                                         command=lambda type=type: addOrganism(type, x, y))
        addOrganismPopup.tk_popup(event.x_root-1, event.y_root-1)

    # def hexWorldPanel(self):
    #     self.hexWorldPanelFrame.pack(pady=100)

    def buildControlPanel(self, panel):
        controlPanel = tk.Frame(panel)
    
        tk.Label(controlPanel, text="Control Panel").pack()
        tk.Label(controlPanel, text="World:").pack()
        time_label = tk.Label(controlPanel, text="    Time: " + str(self.getActiveWorld().checkTime()))
        time_label.pack()
        organisms_label = tk.Label(controlPanel, text="    Organisms: " + str(self.getActiveWorld().getOrganimsCount()))
        organisms_label.pack()
    
        tk.Label(controlPanel, text="Human:").pack()
        human_power = tk.Label(controlPanel, text="    Power: " + (str(self.getActiveWorld().getHuman().getPower()) if self.getActiveWorld().hasHuman() else ""))
        human_power.pack()
    
        def toggleImmortality():
            if not self.getActiveWorld().hasHuman():
                return
            self.getActiveWorld().getHuman().toggleImmortality()
            useImmortality.config(text="🔰 Immortality\n" + self.getActiveWorld().getHuman().getAbilityInfo())
    
        useImmortality = tk.Button(controlPanel, text="🔰 Immortality\n" + (self.getActiveWorld().getHuman().getAbilityInfo() if self.getActiveWorld().hasHuman() else ""), command=toggleImmortality)
        useImmortality.pack()
    
        return controlPanel
        
    def buildLogPanel(self, panel):
        logPanel = tk.Text(panel)
        logPanel.pack(fill=tk.BOTH, expand=True)
        return logPanel
    
    def updateLogPanel(self):
        self.logPanel.delete("1.0", tk.END)
        for log in self.getActiveWorld().getLogs():
            self.logPanel.insert(tk.END, log + '\n')

    def buildGameView(self):
            # Create the main split pane (gameView)
            gameView = tk.PanedWindow(self.root, orient=tk.HORIZONTAL)
        
            # Create the right split pane (rightSplitPane)
            right_split_pane = tk.PanedWindow(gameView, orient=tk.VERTICAL)
        
            # Create the log panel and control panel
            self.logPanel = self.buildLogPanel(right_split_pane)
            self.controlPanel = self.buildControlPanel(right_split_pane)
        
            # Add the log panel and control panel to the right split pane
            right_split_pane.add(self.logPanel)
            right_split_pane.add(self.controlPanel)
        
            # Create the board panel
            self.worldPanel = self.buildSquareWorldPanel(gameView)
        
            # Add the board panel and right split pane to the main split pane
            gameView.add(self.worldPanel)
            gameView.add(right_split_pane)
            
            self.updateLogPanel()
            return gameView