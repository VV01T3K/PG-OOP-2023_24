import random
from typing import List, Optional

from .Tile import Tile
from .GlobalSettings import GlobalSettings
from .Organisms.Organism import Organism
from Utils.DynamicDirections import DynamicDirections

from .Organisms.Plants import *
from .Organisms.Animals import *

from Utils.OrganismFactory import OrganismFactory


class World:

    def __init__(self, width=20, height=20):
        self._width = width
        self._height = height
        self._time = 0
        self._organisms: List[Organism] = []
        self._tiles: List[Tile] = []
        self._logs = []
        self._human: Optional[Human] = None
        self.createBoard(width, height)

    def printWorld(self):
        for y in range(self._height):
            for x in range(self._width):
                tile = self.getTile(x, y)
                if tile is not None:
                    print(tile, end="")
            print()
        print()
        humann = self.getHuman()
        if humann is None:
            return
        human: Human = humann
        print("Human: " + human.getAbilityInfo())

    def printLogs(self):
        for log in self._logs:
            print(log)

    def createBoard(self, width, height):
        DynamicDirections.clear()
        DynamicDirections.addInstance("UP")
        DynamicDirections.addInstance("RIGHT")
        DynamicDirections.addInstance("DOWN")
        DynamicDirections.addInstance("LEFT")
        DynamicDirections.addInstance("SELF")

        for i in range(width * height):
            self._tiles.append(Tile(i, 4))
        for x in range(width):
            for y in range(height):
                tile: Tile = self._tiles[y * width + x]
                if y > 0:
                    tile.setLink(DynamicDirections.get("UP"),
                                 self._tiles[(y - 1) * width + x])
                if x < width - 1:
                    tile.setLink(DynamicDirections.get("RIGHT"),
                                 self._tiles[y * width + x + 1])
                if y < height - 1:
                    tile.setLink(DynamicDirections.get("DOWN"),
                                 self._tiles[(y + 1) * width + x])
                if x > 0:
                    tile.setLink(DynamicDirections.get("LEFT"),
                                 self._tiles[y * width + x - 1])

    def setTime(self, time):
        self._time = time

    def setHuman(self, human):
        self._human = human

    def getHuman(self):
        return self._human

    def hasHuman(self):
        return self._human != None

    def findHuman(self):
        return next((organism for organism in self._organisms if isinstance(organism, Human)), None)

    def addLog(self, log):
        self._logs.append(log)

    def getLogs(self):
        return self._logs

    def clearLogs(self):
        self._logs.clear()

    def populateWorld(self):
        self.resetWorld()
        self.spreadOrganisms(Human(self), 1)
        self.setHuman(self._organisms[-1])

        self.spreadOrganisms(SosnowskyHogweed(self), 5)
        self.spreadOrganisms(Grass(self), 1)
        self.spreadOrganisms(Guarana(self), 3)
        self.spreadOrganisms(Milkweed(self), 1)
        self.spreadOrganisms(Belladonna(self), 2)

        self.spreadOrganisms(Wolf(self), 3)
        self.spreadOrganisms(Sheep(self), 1)
        self.spreadOrganisms(CyberSheep(self), 2)
        self.spreadOrganisms(Fox(self), 3)
        self.spreadOrganisms(Turtle(self), 3)
        self.spreadOrganisms(Antelope(self), 4)

    def cleanTiles(self):
        for tile in self._tiles:
            tile.clear()

    def resetWorld(self):
        self.clearOrganisms()
        self.cleanTiles()
        self.clearLogs()
        self._time = 0

    def setWorld(self, width, height, time):
        self.clearTiles()
        self._width = width
        self._height = height
        self._time = time
        self.createBoard(width, height)

    def checkTime(self):
        return self._time

    def getWidth(self):
        return self._width

    def getHeight(self):
        return self._height

    def getTile(self, x, y=None):
        if y is None:
            return self._tiles[x]
        else:
            return self._tiles[x + y * self._width]

    def setTile(self, x, y, tile):
        self._tiles[x + y * self._width] = tile

    def getOrganism(self, index):
        return self._organisms[index]

    def addOrganism(self, organism: Organism, tile: Tile):
        self._organisms.append(organism)
        organism.setTile(tile)
        tile.placeOrganism(organism)

    def simulate(self):
        self._time += 1
        self.clearLogs()

        self._organisms.sort(
            key=lambda organism: (-organism.getInitiative(), organism.getAge()))

        for organism in self._organisms.copy():
            if organism.isSkipped() or organism.isDead():
                continue
            if not GlobalSettings.AI_ACTION and not isinstance(organism, Human):
                continue

            organism.action()

            tile = organism.getTile()
            if tile is not None and tile.getOrganismCount() > 1:
                other = tile.getOrganism() if tile is not None else None
                if other is None or organism == other or (other is not None and other.isDead()):
                    continue
                organism.collision(other)

        for organism in list(self._organisms):
            if organism.isDead():
                tile = organism.getTile()
                if tile is None:
                    raise Exception("Tile is None")
                tile.removeOrganism(organism)
                if isinstance(organism, Human):
                    self._human = None
                self._organisms.remove(organism)
            else:
                organism.Age()
                organism.unskipTurn()

    def getOrganimsCount(self):
        return len(self._organisms)

    def spreadOrganisms(self, organism, count):
        max = self._width * self._height - 1
        while count > 0 and self.getOrganimsCount() < max:
            tile = self.getTile(random.randint(0, len(self._tiles) - 1))
            if tile.isFree():
                self.addOrganism(organism.construct(), tile)
                count -= 1

    def generateOrganisms(self):
        pass

    def clearOrganisms(self):
        self._organisms.clear()
        self._human = None

    def clearTiles(self):
        self._tiles.clear()

    def linkOrganismsWithTiles(self):
        for organism in self._organisms:
            tile = organism.getTile()
            if tile is not None:
                self.getTile(tile.INDEX).placeOrganism(organism)

    def setOrganisms(self, organisms):
        self.clearOrganisms()
        self._organisms = organisms
        self.linkOrganismsWithTiles()

    def getOrganisms(self):
        return self._organisms

    def setNewOrganism(self, type, x, y):
        tile = self.getTile(x, y)
        while not tile.isFree():
            organism_to_remove = tile.getOrganism()
            if organism_to_remove is not None:
                tile.removeOrganism(organism_to_remove)
                self._organisms.remove(organism_to_remove)
        organism = OrganismFactory(self).createFromType(type)
        organism.skipTurn()
        self.addOrganism(organism, tile)
        self.addLog("New " + type.getSymbol() + " " +
                    type.getName() + " spawned!")


class HexWorld(World):
    def __init__(self, width, height):
        super().__init__(width, height)

    def createBoard(self, width, height):
        DynamicDirections.clear()

        DynamicDirections.addInstance("UP")
        DynamicDirections.addInstance("DOWN")
        DynamicDirections.addInstance("TOP_LEFT")
        DynamicDirections.addInstance("TOP_RIGHT")
        DynamicDirections.addInstance("BOTTOM_LEFT")
        DynamicDirections.addInstance("BOTTOM_RIGHT")
        DynamicDirections.addInstance("SELF")

        size = width * height

        for i in range(size):
            self._tiles.append(Tile(i, 6))

        for x in range(width):
            for y in range(height):
                tile: Tile = self._tiles[y * width + x]

                indexUp = (y - 1) * width + (x - 1)
                up = self._tiles[indexUp] if 0 <= indexUp < len(
                    self._tiles) else None
                indexDown = (y + 1) * width + (x + 1)
                down = self._tiles[indexDown] if 0 <= indexDown < len(
                    self._tiles) else None
                indexBottomRight = y * width + (x + 1)
                bottom_right = self._tiles[indexBottomRight] if 0 <= indexBottomRight < len(
                    self._tiles) else None
                indexBottomLeft = (y + 1) * width + x
                bottom_left = self._tiles[indexBottomLeft] if 0 <= indexBottomLeft < len(
                    self._tiles) else None
                indexTopRight = (y - 1) * width + x
                top_right = self._tiles[indexTopRight] if 0 <= indexTopRight < len(
                    self._tiles) else None
                indexTopLeft = y * width + (x - 1)
                top_left = self._tiles[indexTopLeft] if 0 <= indexTopLeft < len(
                    self._tiles) else None

                tile.setLink(DynamicDirections.get("UP"), up)
                tile.setLink(DynamicDirections.get("DOWN"), down)
                tile.setLink(DynamicDirections.get("TOP_LEFT"), top_left)
                tile.setLink(DynamicDirections.get("TOP_RIGHT"), top_right)
                tile.setLink(DynamicDirections.get("BOTTOM_LEFT"), bottom_left)
                tile.setLink(DynamicDirections.get(
                    "BOTTOM_RIGHT"), bottom_right)

    def setTime(self, time):
        self.time = time
