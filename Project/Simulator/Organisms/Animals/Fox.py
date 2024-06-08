from .Animal import Animal
from Simulator.Organisms.Organism import Type

import random


class Fox(Animal):
    def __init__(self, world, json=None):
        super().__init__(3, 7, world, Type.FOX, json)

    def construct(self):
        return Fox(self._world)

    def action(self):
        neighbours = [neighbour for neighbour in self._tile.getNeighbours() if neighbour and neighbour.isFree(
        ) and (not neighbour.getOrganism() or neighbour.getOrganism().getPower() <= self._power)]

        if not neighbours:
            target = self._tile.getRandomFreeNeighbour()
        else:
            target = random.choice(neighbours)

        self.move(target)
