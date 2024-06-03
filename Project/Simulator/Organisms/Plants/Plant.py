from hmac import new
import json
import random

from abc import ABC, abstractmethod

from Simulator.Tile import Tile
from Simulator.World import World
from Simulator.Organisms.Organism import Organism, Type
from Simulator.GlobalSettings import GlobalSettings


class Plant(Organism, ABC):
    def __init__(self, type, power, initiative, world: World, json=None):
        super().__init__(type, power, initiative, world, json)

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
