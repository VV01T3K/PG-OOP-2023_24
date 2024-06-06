from .Animal import Animal
from Simulator.Organisms.Organism import Type

import random


class Turtle(Animal):
    def __init__(self, world, json=None):
        super().__init__(2, 1, world, Type.TURTLE, json)

    def construct(self):
        return Turtle(self.world)

    def action(self):
        # 75% chance to skip turn
        if random.randint(0, 100) < 75:
            return
        super().action()

    def collisionReaction(self, other):
        if other.getType() == Type.TURTLE:
            return False
        if other.getPower() < 5:
            other.undoMove()
            self.world.addLog(f"{other.getSymbol()} tried to attack "
                              f"{self.getSymbol()} but failed!")
            return True
        return False
