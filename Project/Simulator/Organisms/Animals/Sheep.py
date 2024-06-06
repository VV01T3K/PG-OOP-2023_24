from .Animal import Animal
from Simulator.Organisms.Organism import Type


class Sheep(Animal):
    def __init__(self, world, json=None):
        super().__init__(4, 4, world, Type.SHEEP, json)

    def construct(self):
        return Sheep(self.world)
