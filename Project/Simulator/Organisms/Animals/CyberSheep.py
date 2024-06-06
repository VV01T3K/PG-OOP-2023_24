from .Animal import Animal
from Simulator.Organisms.Organism import Type


class CyberSheep(Animal):
    def __init__(self, world, json=None):
        super().__init__(11, 4, world, Type.CYBER_SHEEP, json)

    def construct(self):
        return CyberSheep(self.world)
