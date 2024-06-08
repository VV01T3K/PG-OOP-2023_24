from .Animal import Animal
from Simulator.Organisms.Organism import Type, Organism

import random


class Antelope(Animal):
    def __init__(self, world, json=None):
        super().__init__(4, 4, world, Type.ANTELOPE, json)

    def construct(self):
        return Antelope(self._world)

    def action(self):
        super().action()
        if self._tile.getOrganismCount() > 1:
            organism = self._tile.getOrganism()
            if organism is not None and organism.isAlive():
                return
        neighbours = list(self._tile.getNeighbours())
        if self._oldTile is None:
            return
        neighbours.remove(self._oldTile)  # type: ignore
        if not neighbours:
            return
        new_tile = neighbours[random.randint(0, len(neighbours) - 1)]
        self.move(new_tile)

    def collision(self, other: Organism):
        if other.getType() == Type.ANTELOPE:
            super().collision(other)
        elif random.randint(0, 100) < 50:
            newTile = self._tile.getRandomFreeNeighbour()
            if newTile is None:
                super().collision(other)
                return
            self.move(newTile)
            self._world.addLog(
                f"{self.getSymbol()} escaped from "f"{other.getSymbol()}!")
        else:
            super().collision(other)

    def collisionReaction(self, other):
        if other.getType() == Type.ANTELOPE:
            return False
        if random.randint(0, 100) < 50:
            newTile = self._tile.getRandomFreeNeighbour()
            if newTile is None:
                return False
            self.move(newTile)
            return True
        return False
