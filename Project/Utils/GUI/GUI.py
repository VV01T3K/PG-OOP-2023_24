import sys
import tkinter as tk
from tkinter import Toplevel, ttk, messagebox

from Simulator.World import World, HexWorld
from Simulator.Organisms.Organism import Type
from .KeyBindings import KeyBindings
from GlobalSettings import GlobalSettings
from Utils.FileHandler import FileHandler


class GUI:
    def __init__(self, world: World):
        self.__world = world
        self.__root = tk.Tk()
        self.__root.title("Toolbar Example")
        self.__root.geometry("900x650")
        self.__saveToolBar = None
        self.__toolbar = self.buildToolBar()
        self.__menuButtons = []
        self.__menu = self.buildMenu()
        self.__form = self.buildForm()
        self.__controlPanel = None
        self.__logPanel = None
        self.__worldPanel = None
        self.__buttons = {}
        self.__controlPanelStore = {}
        self.__gameView = None
        self.__gameView = self.buildGameView()

        self.__keyBindings = KeyBindings(self)

    def getRoot(self) -> tk.Tk:
        return self.__root

    def getControlPanelStore(self) -> dict[str, tk.Button]:
        return self.__controlPanelStore

    def run(self):
        self.showMenu()
        self.__root.mainloop()

    def getActiveWorld(self) -> World:
        return self.__world

    def buildMenu(self):
        def continueGame():
            self.showGameView()

        def startGame():
            self.showForm()

        def loadGame():
            self.loadPopUp()

        def exitGame():
            self.__root.destroy()
            sys.exit()

        menu_frame = tk.Frame(self.__root)

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

        self.__menuButtons.append(continue_button)
        self.__menuButtons.append(start_button)
        self.__menuButtons.append(load_button)
        self.__menuButtons.append(exit_button)

        self.continueButton = continue_button

        return menu_frame

    def savePopUp(self):
        def on_ok():
            savename = name.get()
            if savename:
                FileHandler.saveWorld(self.__world, savename)
                messagebox.showinfo("Saved", "Game saved successfully")
            top.destroy()
        top = Toplevel()
        top.geometry("250x70")
        top.title("Save game")
        ttk.Label(top, text="Enter the name of the save file").pack()
        name = ttk.Entry(top)
        name.pack()

        ttk.Button(top, text="OK", command=on_ok).pack()

    def loadPopUp(self):
        saves = FileHandler.listSaves()
        if not saves:
            messagebox.showerror("Error", "No saves found")
            return

        def on_ok():
            save = combo.get()
            if save:
                self.__world = FileHandler.loadWorld(save)
                self.__gameView = self.buildGameView()
                self.showGameView()
            top.destroy()
        top = Toplevel()
        top.geometry("250x70")
        top.title("Load game")
        ttk.Label(top, text="Choose a save to load").pack()
        combo = ttk.Combobox(top, values=saves, state="readonly")
        combo.pack()
        combo.set(saves[0])
        ttk.Button(top, text="OK", command=on_ok).pack()

    def buildForm(self):
        root = self.__root
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

            if not width.isdigit() or not height.isdigit() or int(width) < 1 or int(height) < 1 or int(width) > 40 or int(height) > 40:
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

        def createWorld(width, height, world_type):
            if (world_type == "Square"):
                self.__world = World(width, height)
            else:
                self.__world = HexWorld(width, height)
            self.__world.populateWorld()
            self.__world.setHuman(self.__world.findHuman())
            self.__gameView = self.buildGameView()

        def submit():
            if validate_input():
                createWorld(int(width_entry.get()),
                            int(height_entry.get()), world_type.get())
                self.showGameView()

        submit_button = tk.Button(
            form_frame, text="Submit", font=larger_font, command=submit)
        submit_button.grid(row=3, column=0, columnspan=4, padx=10, pady=20)

        return form_frame

    def resetFrames(self):
        self.__root.focus_set()
        self.__keyBindings.resetKeyBindings()
        self.__menu.pack_forget()
        self.__form.pack_forget()
        self.hideToolBar()
        self.__worldPanel.pack_forget()
        self.__logPanel.pack_forget()
        self.__controlPanel.pack_forget()
        self.__gameView.pack_forget()
        self.__saveToolBar.pack_forget()

    def showMenu(self):
        self.resetFrames()
        for button in self.__menuButtons:
            button.pack_forget()
        for button in self.__menuButtons:
            button.pack(pady=10)
        if (not (not self.getActiveWorld() == None and self.getActiveWorld().checkTime() > 0)):
            self.__menuButtons[0].pack_forget()
        self.__menu.pack(pady=100)

    def showForm(self):
        self.resetFrames()
        self.showToolBar()
        self.__form.pack(pady=100)

    def showToolBar(self):
        self.__toolbar.pack(side=tk.TOP, fill=tk.X)

    def showExtendedToolBar(self):
        self.__saveToolBar.pack(side=tk.LEFT, padx=2, pady=2)
        self.__toolbar.pack(side=tk.TOP, fill=tk.X)

    def showGameView(self):
        self.__keyBindings.resetKeyBindings()
        self.resetFrames()
        if (isinstance(self.getActiveWorld(), HexWorld)):
            self.__keyBindings.hexagonalKeyBindings()
        else:
            self.__keyBindings.squareKeyBindings()
        self.showExtendedToolBar()
        self.__gameView.pack(fill=tk.BOTH, expand=1)

    def buildToolBar(self):
        toolbar = tk.Frame(self.__root, bd=1, relief=tk.RAISED)

        menu = tk.Button(toolbar, text="Menu",
                         relief=tk.FLAT, command=self.showMenu)
        menu.pack(side=tk.LEFT, padx=2, pady=2)

        save = tk.Button(toolbar, text="Save",
                         relief=tk.FLAT, command=self.savePopUp)
        save.pack(side=tk.LEFT, padx=2, pady=2)
        self.__saveToolBar = save

        return toolbar

    def hideToolBar(self):
        self.__toolbar.pack_forget()

    def buildSquareWorldPanel(self, panel):
        width = self.getActiveWorld().getWidth()
        height = self.getActiveWorld().getHeight()
        squareWorldPanelFrame = tk.Frame(panel)
        self.__buttons = {}
        for x in range(width):
            for y in range(height):
                button = tk.Button(
                    squareWorldPanelFrame, text=f'({x},{y})', font=("default", 20), width=3)
                button.grid(row=y, column=x)
                self.__buttons[(x, y)] = button
                button.config(command=lambda x=x,
                              y=y: self.useAddOrganismPopup(x, y))

        self.updateButtonsText()
        return squareWorldPanelFrame

    def buildHexWorldPanel(self, panel):
        width = self.getActiveWorld().getWidth()
        height = self.getActiveWorld().getHeight()
        squareWorldPanelFrame = tk.Frame(panel)
        self.__buttons = {}
        fontsize = 20
        square_size = fontsize * 2
        panel_width = square_size * max(width, height) * 2
        squareWorldPanelFrame.config(width=panel_width)
        for j in range(width):
            for i in range(height):
                button = tk.Button(
                    squareWorldPanelFrame, text=f'({j},{i})', font=("default", 20), width=3)
                x = (i - j) * square_size + panel_width // 2 - square_size//2
                y = (i + j) * square_size // 2 + square_size//2
                button.place(x=x, y=y,
                             width=square_size, height=square_size)
                self.__buttons[(j, i)] = button
                button.config(command=lambda x=j,
                              y=i: self.useAddOrganismPopup(x, y))

        self.updateButtonsText()
        return squareWorldPanelFrame

    def updateButtonsText(self):
        for x in range(self.getActiveWorld().getWidth()):
            for y in range(self.getActiveWorld().getHeight()):
                self.updateButtonText(x, y)

    def updateButtonText(self, x, y):
        button = self.__buttons[(x, y)]
        symbol = f'{self.getActiveWorld().getTile(x, y)}'
        if (symbol == "🔳"):
            symbol = "    "
        button.config(text=symbol)

    def useAddOrganismPopup(self, x, y):
        def addOrganism(type, x, y):
            self.getActiveWorld().setNewOrganism(type, x, y)
            if type == Type.HUMAN:
                self.getActiveWorld().setHuman(self.getActiveWorld().findHuman())
                self.getActiveWorld().getHuman().unskipTurn()
                self.updateControlPanel()
            self.updateButtonText(x, y)
            self.updateLogPanel()

        addOrganismPopup = tk.Menu(self.__root, tearoff=0)
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
        addOrganismPopup.tk_popup(
            addOrganismPopup.winfo_pointerx()+1, addOrganismPopup.winfo_pointery()+1)

    def buildControlPanel(self, panel):
        controlPanel = tk.Frame(panel)

        tk.Label(controlPanel, text="Control Panel").pack(fill='x')
        tk.Label(controlPanel, text="World:", anchor='w').pack(fill='x')
        time_label = tk.Label(controlPanel, anchor='w')
        time_label.pack(fill='x')
        organisms_label = tk.Label(controlPanel, anchor='w')
        organisms_label.pack(fill='x')

        tk.Label(controlPanel, text="Human:", anchor='w').pack(fill='x')
        human_power = tk.Label(controlPanel, anchor='w')
        human_power.pack(fill='x')

        def toggleImmortality():
            if not self.getActiveWorld().hasHuman():
                return
            self.getActiveWorld().getHuman().toggleImmortality()
            useImmortality.config(
                text="🔰 Immortality\n" + self.getActiveWorld().getHuman().getAbilityInfo())

        useImmortality = tk.Button(controlPanel, command=toggleImmortality)
        useImmortality.pack(fill='x')

        def nextRound():
            if (not GlobalSettings.HUMAN_AI and self.getActiveWorld().hasHuman() and self.getActiveWorld().getHuman().getNextMove() == "Give direction"):
                return
            self.getActiveWorld().simulate()
            self.updateLogPanel()
            self.updateButtonsText()
            self.updateControlPanel()

        nextRoundButton = tk.Button(
            controlPanel, command=nextRound, bg='light green')
        nextRoundButton.pack(fill='x')

        self.__controlPanelStore = {
            "time": time_label,
            "organisms": organisms_label,
            "human": human_power,
            "useImmortality": useImmortality,
            "nextRound": nextRoundButton,
        }

        self.updateControlPanel()

        return controlPanel

    def updateControlPanel(self):
        self.__controlPanelStore["time"].config(
            text="    Time: " + str(self.getActiveWorld().checkTime()))
        self.__controlPanelStore["organisms"].config(
            text="    Organisms: " + str(self.getActiveWorld().getOrganimsCount()))
        if self.getActiveWorld().hasHuman():
            self.__controlPanelStore["human"].config(
                text="    Power: " + (str(self.getActiveWorld().getHuman().getPower())))
            self.__controlPanelStore["useImmortality"].config(
                text="🔰 Immortality\n" + self.getActiveWorld().getHuman().getAbilityInfo())
            self.__controlPanelStore["nextRound"].config(
                text="Next Turn\n" + str(self.getActiveWorld().getHuman().getNextMove()))
            self.__controlPanelStore["useImmortality"].config(state=tk.NORMAL)
        else:
            self.__controlPanelStore["human"].config(text="")
            self.__controlPanelStore["useImmortality"].config(
                state=tk.DISABLED)
            self.__controlPanelStore["useImmortality"].config(
                text="🔰 Immortality\nNo human in the world")
            self.__controlPanelStore["nextRound"].config(
                text="Next Turn\nNo human in the world")
        if (GlobalSettings.HUMAN_AI):
            self.__controlPanelStore["nextRound"].config(
                text="Next Turn\nAI controlled")
            self.__controlPanelStore["useImmortality"].config(
                state=tk.DISABLED)

    def buildLogPanel(self, panel):
        logPanel = tk.Text(panel)
        logPanel.config(state=tk.DISABLED)
        return logPanel

    def updateLogPanel(self):
        self.__logPanel.config(state=tk.NORMAL)
        self.__logPanel.delete("1.0", tk.END)
        for log in self.getActiveWorld().getLogs():
            self.__logPanel.insert(tk.END, log + '\n')
        self.__logPanel.config(state=tk.DISABLED)

    def buildGameView(self):
        gameView = tk.PanedWindow(
            self.__root, orient=tk.HORIZONTAL, sashrelief=tk.RAISED, sashwidth=0)
        right_split_pane = tk.PanedWindow(
            gameView, orient=tk.VERTICAL, sashrelief=tk.RAISED, sashwidth=0)
        self.__logPanel = self.buildLogPanel(right_split_pane)
        self.__controlPanel = self.buildControlPanel(right_split_pane)
        right_split_pane.add(self.__logPanel)
        right_split_pane.add(self.__controlPanel)
        if (isinstance(self.getActiveWorld(), HexWorld)):
            self.__worldPanel = self.buildHexWorldPanel(gameView)
        else:
            self.__worldPanel = self.buildSquareWorldPanel(gameView)
        gameView.add(self.__worldPanel)
        gameView.add(right_split_pane)

        self.updateLogPanel()
        return gameView
