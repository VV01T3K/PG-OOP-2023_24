import random


class Tile:
    def __init__(self, index, directionCount):
        self.index = index
        self.directions = [None]*directionCount
        self.organisms = []

    def __str__(self):
        return '' if not self.organisms else self.organisms[0].get_symbol()

    def clear(self):
        self.organisms.clear()

    def setLink(self, direction, tile):
        self.directions[direction.ordinal()] = tile

    def getOrganism(self):
        return self.organisms[0] if len(self.organisms) > 0 else None

    def placeOrganism(self, organism):
        self.organisms.append(organism)

    def removeOrganism(self, organism):
        self.organisms.remove(organism)

    def getRandomFreeNeighbour(self):
        freeNeighbours = [
            tile for tile in self.directions if tile != None and tile.isFree()]
        if len(freeNeighbours) == 0:
            return None
        return freeNeighbours[random.randint(0, len(freeNeighbours) - 1)]

    def getNeighbour(self, direction):
        return self.directions[direction.ordinal()]

    def getRandomNeighbour(self):
        neighbours = [tile for tile in self.directions if tile != None]
        if len(neighbours) == 0:
            return None
        return neighbours[random.randint(0, len(neighbours) - 1)]

    def isFree(self):
        return len(self.organisms) == 0

    def getNeighbours(self):
        return self.directions

    def getOccupiedNeighbours(self):
        occupiedNeighbours = [
            tile for tile in self.directions if tile != None and not tile.isFree()]
        return occupiedNeighbours

    def getOrganismCount(self):
        return len(self.organisms)
