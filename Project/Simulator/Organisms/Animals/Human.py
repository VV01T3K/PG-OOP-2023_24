from .Animal import Animal
from Simulator.Organisms.Organism import Type


class Human(Animal):
    def __init__(self, world, json=None):
        super().__init__(5, 4, world, Type.HUMAN, json)

    def construct(self):
        return Human(self.world)
