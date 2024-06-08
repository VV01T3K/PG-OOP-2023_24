import random
from typing import List

from .Organisms.Organism import Organism


class Tile:
    def __init__(self, index, directionCount):
        self.INDEX = index
        self.__directions = [None]*directionCount
        self.__organisms = []
        self.__parent = None

    def __str__(self):
        return '🔳' if not self.__organisms else self.__organisms[0].getSymbol()

    def clear(self):
        self.__organisms.clear()

    def getParent(self):
        return self.__parent

    def setParent(self, parent):
        self.__parent = parent

    def setLink(self, direction, tile):
        if (direction == None):
            return
        self.__directions[direction.ordinal()] = tile

    def getOrganism(self):
        return self.__organisms[0] if len(self.__organisms) > 0 else None

    def placeOrganism(self, organism: Organism):
        self.__organisms.append(organism)

    def removeOrganism(self, organism: Organism):
        self.__organisms.remove(organism)

    def getRandomFreeNeighbour(self):
        freeNeighbours = [
            tile for tile in self.__directions if tile != None and tile.isFree()]
        if len(freeNeighbours) == 0:
            return None
        return freeNeighbours[random.randint(0, len(freeNeighbours) - 1)]

    def getNeighbour(self, direction):
        return self.__directions[direction.ordinal()]

    def getRandomNeighbour(self):
        neighbours = [tile for tile in self.__directions if tile != None]
        if len(neighbours) == 0:
            return None
        return neighbours[random.randint(0, len(neighbours) - 1)]

    def isFree(self):
        return len(self.__organisms) == 0

    def getNeighbours(self):
        neighbours = []
        for direction in self.__directions:
            if direction is not None:
                neighbours.append(direction)
        return neighbours

    def getOccupiedNeighbours(self):
        occupiedNeighbours = [
            tile for tile in self.__directions if tile != None and not tile.isFree()]
        return occupiedNeighbours

    def getOrganismCount(self):
        return len(self.__organisms)
