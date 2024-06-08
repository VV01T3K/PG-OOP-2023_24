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
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: UP")

        def moveDown(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("DOWN"))
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: DOWN")

        def moveLeft(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("LEFT"))
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: LEFT")

        def moveRight(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("RIGHT"))
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: RIGHT")

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
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: UP")

        def moveDown(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("DOWN"))
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: DOWN")

        def moveTopLeft(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("TOP_RIGHT"))
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: TOP RIGHT")

        def moveBottomLeft(e):
            gui.getActiveWorld().getHuman().setNextMove(
                DynamicDirections.get("BOTTOM_RIGHT"))
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: BOTTOM RIGHT")

        def moveTopRight(e):
            gui.getActiveWorld().getHuman().setNextMove(DynamicDirections.get("TOP_LEFT"))
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: TOP LEFT")

        def moveBottomRight(e):
            gui.getActiveWorld().getHuman().setNextMove(
                DynamicDirections.get("BOTTOM_LEFT"))
            self.gui.controlPanelStore["nextRound"].config(
                text="Next Turn\nMove: BOTTOM LEFT")

        def nextRound(e):
            self.gui.controlPanelStore["nextRound"].invoke()

        root.bind("<space>", nextRound)

        root.bind("q", moveTopLeft)
        root.bind("w", moveUp)
        root.bind("e", moveTopRight)
        root.bind("a", moveBottomLeft)
        root.bind("s", moveDown)
        root.bind("d", moveBottomRight)

        root.bind("<Home>", moveTopLeft)
        root.bind("<Up>", moveUp)
        root.bind("<Prior>", moveTopRight)
        root.bind("<End>", moveBottomLeft)
        root.bind("<Down>", moveDown)
        root.bind("<Next>", moveBottomRight)

    def resetKeyBindings(self):
        keys = ["q,", "w", "e", "a", "s", "d", "<space>", "<Up>", "<Down>", "<Left>", "<Right>",
                "<Up>", "<Down>", "<Home>",
                "<Prior>", "<End>", "<Next>"]
        for key in keys:
            self.root.unbind(key)
