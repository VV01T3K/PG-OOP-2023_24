from Simulator.Organisms.Organism import Organism
from typing import Optional

from .Ability import Ability
from Simulator.Organisms.Animals.Animal import Animal
from Simulator.Organisms.Animals.Human import Human


class Immortality(Ability):
    def __init__(self, cooldown, duration, default_cooldown=-1, default_duration=-1):
        if (default_cooldown == -1) or (default_duration == -1):
            super().__init__(cooldown, duration)
        else:
            super().__init__(cooldown, duration, 5, 5)

    def effect(self, user: Organism, other: Optional[Organism] = None):
        if other is None:
            return
        if user is None:
            return

        if (other is None):
            userTile = user.getTile()
            if (userTile is None):
                return
            newTile = userTile.getRandomFreeNeighbour()
            if newTile is None:
                newTile = userTile.getRandomNeighbour()
            if newTile is None:
                if (isinstance(other, Animal)):
                    other.undoMove()
                return
            if (isinstance(user, Human)):
                user.move(newTile)
            if (userTile.getOrganismCount() > 1):
                user.collision(userTile.getOrganism())
        else:
            newTile = user.getTile()
            if (newTile is None):
                return
            newTile = newTile.getRandomFreeNeighbour()
            if newTile is None:
                return
            if (isinstance(user, Human)):
                user.move(newTile)
