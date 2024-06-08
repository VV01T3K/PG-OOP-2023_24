import tkinter as tk
from Utils.DynamicDirections import DynamicDirections

class KeyBindings:
    def __init__(self, gui):
        self.root: tk.Tk = gui.root
        self.gui = gui

    def squareKeyBindings(self):
        from .GUI import GUI
        root = self.root
        gui: GUI = self.gui
        self.resetKeyBindings()

        def moveUp(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("UP"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: UP")
            
        def moveDown(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("DOWN"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: DOWN")

        def moveLeft(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("LEFT"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: LEFT")

        def moveRight(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("RIGHT"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: RIGHT")

        def nextRound(e):
            self.gui.controlPanelStore["nextRound"].invoke()

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
        from .GUI import GUI
        root = self.root
        gui: GUI = self.gui
        self.resetKeyBindings()
        
        def moveUp(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("UP"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: UP")

        def moveDown(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("DOWN"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: DOWN")

        def moveTopLeft(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("TOP_LEFT"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: TOP LEFT")

        def moveBottomLeft(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("BOTTOM_LEFT"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: BOTTOM LEFT")

        def moveTopRight(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("TOP_RIGHT"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: TOP RIGHT")

        def moveBottomRight(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("BOTTOM_RIGHT"))
            self.gui.controlPanelStore["nextRound"].config(text="Next Turn\nMove: BOTTOM RIGHT")

        def nextRound(e):
            self.gui.controlPanelStore["nextRound"].invoke()

        root.bind("<space>", nextRound)

        root.bind("q", moveTopLeft)
        root.bind("w", moveUp)
        root.bind("e", moveTopRight)
        root.bind("a", moveBottomLeft)
        root.bind("s", moveDown)
        root.bind("d", moveBottomRight)

        root.bind("<KP_Up>", moveUp)
        root.bind("<KP_Down>", moveDown)
        root.bind("<KP_Home>", moveTopLeft)
        root.bind("<KP_Prior>", moveTopRight)
        root.bind("<KP_End>", moveBottomLeft)
        root.bind("<KP_Next>", moveBottomRight)

    def resetKeyBindings(self):
        keys = ["q,", "w", "e", "a", "s", "d", "<space>", "<Up>", "<Down>", "<Left>", "<Right>",
                "<KP_Up>", "<KP_Down>", "<KP_Home>",
                "<KP_Prior>", "<KP_End>", "<KP_Next>"]
        for key in keys:
            self.root.unbind(key)
