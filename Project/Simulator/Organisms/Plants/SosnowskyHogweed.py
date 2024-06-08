import re
from .Plant import Plant
from Simulator.Organisms.Organism import Type, Organism


class SosnowskyHogweed(Plant):
    def __init__(self, world, json=None):
        super().__init__(10, world, Type.SOSNOWSKY_HOGWEED, json)

    def construct(self):
        return SosnowskyHogweed(self._world)

    def action(self):
        super().action()
        killed = []
        if self._tile is None:
            return
        for neighbour in self._tile.getOccupiedNeighbours():
            organism = neighbour.getOrganism()
            if isinstance(organism, Plant):
                continue
            if organism.getType() == Type.CYBER_SHEEP:
                continue

            organism.die()
            if organism.isDead():
                killed.append(organism.getSymbol())
        if not killed:
            return
        log = self.getSymbol() + " killed " + ", ".join(killed)
        self._world.addLog(log + "!")
        killed.clear()

    def collisionReaction(self, other: Organism):
        if isinstance(other, Plant):
            return False
        if other.getType() == Type.CYBER_SHEEP:
            return False
        other.die()
        self.die()
        self._world.addLog(f"{other.getSymbol()} ate " +
                           self.getSymbol() + " and died!")
        return True
