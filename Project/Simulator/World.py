import random

from Tile import Tile


class World:

    # public World(boolean skip) {}
    def __init__(self, width=20, height=20):
        self.width = width
        self.height = height
        self.time = 0
        self.organisms = []
        self.tiles = []
        self.logs = []
        # self.human = None;
        self.createBoard(width, height)

    def setTime(self, time):
        self.time = time

    def setHuman(self, human):
        self.human = human

    def getHuman(self):
        return self.human

    def hasHuman(self):
        return self.human != None

    # def findHuman(self):
    #     return next((organism for organism in self.organisms if isinstance(organism, Human)), None)

    def addLog(self, log):
        self.logs.append(log)

    def getLogs(self):
        return self.logs

    def clearLogs(self):
        self.logs.clear()

    def populateWorld(self):
        self.resetWorld()

        # self.spreadOrganisms(Human(self), 1)
        # self.setHuman(self.organisms[-1])

        # self.spreadOrganisms(SosnowskyHogweed(self), 3)
        # self.spreadOrganisms(Grass(self), 3)
        # self.spreadOrganisms(Guarana(self), 3)
        # self.spreadOrganisms(Milkweed(self), 3)
        # self.spreadOrganisms(WolfBerries(self), 3)

        # self.spreadOrganisms(Wolf(self), 3)
        # self.spreadOrganisms(Sheep(self), 3)
        # self.spreadOrganisms(CyberSheep(self), 3)
        # self.spreadOrganisms(Fox(self), 3)
        # self.spreadOrganisms(Turtle(self), 3)
        # self.spreadOrganisms(Antelope(self), 3)

    def cleanTiles(self):
        for tile in self.tiles:
            tile.clear()

    def resetWorld(self):
        self.clearOrganisms()
        self.cleanTiles()
        self.clearLogs()
        self.time = 0

    def setWorld(self, width, height, time):
        self.clearTiles()
        self.width = width
        self.height = height
        self.time = time
        self.createBoard(width, height)

    def createBoard(self, width, height):
        # self.tiles = [Tile(i) for i in range(width * height)]
        # for y in range(height):
        #     for x in range(width):
        #         tile = self.tiles[y * width + x]
        #         if y > 0:
        #             tile.setLink(
        #                 Direction.UP, self.tiles[(y - 1) * width + x])
        #         if x < width - 1:
        #             tile.setLink(Direction.RIGHT,
        #                          self.tiles[y * width + x + 1])
        #         if y < height - 1:
        #             tile.setLink(Direction.DOWN,
        #                          self.tiles[(y + 1) * width + x])
        #         if x > 0:
        #             tile.setLink(Direction.LEFT,
        #                          self.tiles[y * width + x - 1])
        pass

    def checkTime(self):
        return self.time

    def getWidth(self):
        return self.width

    def getHeight(self):
        return self.height

    def getTile(self, index):
        return self.tiles[index]

    def getTile(self, x, y):
        return self.tiles[x + y * self.width]

    def setTile(self, x, y, tile):
        self.tiles[x + y * self.width] = tile

    def getOrganism(self, index):
        return self.organisms[index]

    def addOrganism(self, organism, tile):
        self.organisms.append(organism)
        organism.setTile(tile)
        tile.placeOrganism(organism)

    def simulate(self):
        self.time += 1
        self.clearLogs()

        self.organisms.sort(
            key=lambda organism: (-organism.getInitiative(), organism.getAge()))

        for organism in self.organisms.copy():
            if organism.isSkipped() or organism.isDead():
                continue
            if not GlobalSettings.AI_ACTION and not isinstance(organism, Human):
                continue

            organism.action()

            if organism.getTile().getOrganismCount() > 1:
                other = organism.getTile().getOrganism()
                if organism == other or other.isDead():
                    continue
                organism.collision(other)

        self.organisms = [
            organism for organism in self.organisms if not organism.isDead()]
        for organism in self.organisms:
            organism.age()
            organism.unskipTurn()
            if organism.isDead():
                organism.getTile().removeOrganism(organism)
                if isinstance(organism, Human):
                    self.human = None

    def getOrganimsCount(self):
        return len(self.organisms)

    def spreadOrganisms(self, organism, count):
        max = self.width * self.height - 1
        while count > 0 and self.getOrganimsCount() < max:
            tile = self.getTile(random.randint(0, len(self.tiles) - 1))
            if tile.isFree():
                self.addOrganism(organism.construct(), tile)
                count -= 1

    def generateOrganisms(self):
        pass

    def clearOrganisms(self):
        self.organisms.clear()
        self.human = None

    def clearTiles(self):
        self.tiles.clear()

    def linkOrganismsWithTiles(self):
        for organism in self.organisms:
            self.getTile(organism.getTile().index).placeOrganism(organism)

    def setOrganisms(self, organisms):
        self.clearOrganisms()
        self.organisms = organisms
        self.linkOrganismsWithTiles()

    def getOrganisms(self):
        return self.organisms

    def setNewOrganisms(self, type, x, y):
        tile = self.getTile(x, y)
        while not tile.isFree():
            tile.removeOrganism(tile.getOrganism())
        organism = type.construct(self)
        organism.skipTurn()
        self.addOrganism(organism, tile)
        self.addLog("New " + type.getSymbol() + " " + type + " spawned!")
