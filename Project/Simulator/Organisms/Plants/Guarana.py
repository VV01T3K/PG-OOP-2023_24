from .Plant import Plant
from Simulator.Organisms.Organism import Type, Organism


class Guarana(Plant):
    def __init__(self, world, json=None):
        super().__init__(0, world, Type.GUARANA, json)

    def construct(self):
        return Guarana(self.world)

    def collisionReaction(self, other: Organism):
        other.setPower(other.getPower() + 3)
        self.die()
        self.world.addLog(f"{other.getSymbol()} ate {self.getSymbol()} and gained 3 power!")
        return True
