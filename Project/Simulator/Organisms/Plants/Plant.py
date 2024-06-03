import random

from abc import ABC, abstractmethod

from Simulator.Organisms.Organism import Organism
from Simulator.GlobalSettings import GlobalSettings


class Plant(Organism, ABC):
    def __init__(self, power, world, type, json=None):
        super().__init__(type, power, 0, world, json)
        self.reproduction_cooldown = 5

    def action(self):
        if not GlobalSettings.AI_REPRODUCE:
            return
        if random.randint(0, 100) < 5:
            if self.tile is not None:
                newtile = self.tile.getRandomFreeNeighbour()
                if newtile is None:
                    return
                newPlant = self.construct()
                if newPlant is None:
                    return
                newPlant.skipTurn()
                self.world.addOrganism(newPlant, newtile)

                self.world.addLog(self.getSymbol() + " is spreading!!")

    def collision(self, other):
        pass

    def collisionReaction(self, other):
        return False

    def setSpreadCooldown(self, cooldown):
        self.reproduction_cooldown = cooldown

    def getSpreadCooldown(self):
        return self.reproduction_cooldown

    @abstractmethod
    def construct(self):
        pass
