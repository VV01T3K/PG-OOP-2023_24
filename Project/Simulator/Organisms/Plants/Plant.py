import random

from abc import ABC, abstractmethod

from Simulator.Organisms.Organism import Organism
from Simulator.GlobalSettings import GlobalSettings


class Plant(Organism, ABC):
    def __init__(self, power, world, type, json=None):
        super().__init__(type, power, 0, world, json)
        self._reproduction_cooldown = 5

    def action(self):
        if not GlobalSettings.AI_REPRODUCE:
            return
        if random.randint(0, 100) < 5:
            if self._tile is not None:
                newtile = self._tile.getRandomFreeNeighbour()
                if newtile is None:
                    return
                newPlant = self.construct()
                if newPlant is None:
                    return
                newPlant.skipTurn()
                self._world.addOrganism(newPlant, newtile)

                self._world.addLog(self.getSymbol() + " is spreading!!")

    def collision(self, other):
        pass

    def collisionReaction(self, other):
        return False

    def setSpreadCooldown(self, cooldown):
        self._reproduction_cooldown = cooldown

    def getSpreadCooldown(self):
        return self._reproduction_cooldown

    @abstractmethod
    def construct(self):
        pass
