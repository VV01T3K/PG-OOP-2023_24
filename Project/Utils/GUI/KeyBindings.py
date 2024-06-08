from tkinter import Button, Tk
from Utils.DynamicDirections import DynamicDirections


class KeyBindings:
    def __init__(self, gui):
        self.__gui = gui

    def squareKeyBindings(self):
        from .GUI import GUI
        gui: GUI = self.__gui
        root: Tk = gui.getRoot()
        controlPanelStore: dict[str, Button] = gui.getControlPanelStore()
        self.resetKeyBindings()

        def moveUp(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(DynamicDirections.get("UP"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: UP")

        def moveDown(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(DynamicDirections.get("DOWN"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: DOWN")

        def moveLeft(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(DynamicDirections.get("LEFT"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: LEFT")

        def moveRight(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(DynamicDirections.get("RIGHT"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: RIGHT")

        def nextRound(e):
            controlPanelStore["nextRound"].invoke()

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
        gui: GUI = self.__gui
        root: Tk = gui.getRoot()
        controlPanelStore: dict[str, Button] = gui.getControlPanelStore()
        self.resetKeyBindings()

        def moveUp(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(DynamicDirections.get("UP"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: UP")

        def moveDown(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(DynamicDirections.get("DOWN"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: DOWN")

        def moveTopLeft(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(DynamicDirections.get("TOP_RIGHT"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: TOP RIGHT")

        def moveBottomLeft(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(
                    DynamicDirections.get("BOTTOM_RIGHT"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: BOTTOM RIGHT")

        def moveTopRight(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(DynamicDirections.get("TOP_LEFT"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: TOP LEFT")

        def moveBottomRight(e):
            human = gui.getActiveWorld().getHuman()
            if human is not None:
                human.setNextMove(
                    DynamicDirections.get("BOTTOM_LEFT"))
                controlPanelStore["nextRound"].config(
                    text="Next Turn\nMove: BOTTOM LEFT")

        def nextRound(e):
            controlPanelStore["nextRound"].invoke()

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
        from .GUI import GUI
        gui: GUI = self.__gui
        keys = ["q,", "w", "e", "a", "s", "d", "<space>", "<Up>", "<Down>", "<Left>", "<Right>",
                "<Up>", "<Down>", "<Home>",
                "<Prior>", "<End>", "<Next>"]
        for key in keys:
            gui.getRoot().unbind(key)
