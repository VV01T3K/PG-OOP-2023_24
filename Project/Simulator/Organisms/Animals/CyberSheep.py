import re
from tracemalloc import start
from .Animal import Animal
from Simulator.Organisms.Organism import Type
from Simulator.Organisms.Plants.SosnowskyHogweed import SosnowskyHogweed

from collections import deque


class CyberSheep(Animal):
    def __init__(self, world, json=None):
        super().__init__(11, 4, world, Type.CYBER_SHEEP)

    def construct(self):
        return CyberSheep(self._world)

    def pathfind(self):
        queue = deque()
        queue.append(self._tile)
        visited = set([self._tile])
        found = None
        while queue:
            current = queue.popleft()
            if isinstance(current.getOrganism(), SosnowskyHogweed):
                found = current
                break
            for neighbour in current.getNeighbours():
                if neighbour in visited:
                    continue
                visited.add(neighbour)
                queue.append(neighbour)
                neighbour.setParent(current)
        if found is None:
            return None
        queue.clear()
        queue.append(current)
        visited.remove(current)
        while queue:
            current = queue.popleft()
            if (current.getParent() is self._tile):
                return current
            for neighbour in current.getNeighbours():
                if neighbour not in visited:
                    continue
                visited.remove(neighbour)
                queue.append(neighbour)
        raise Exception("Error of pathfinding")

    def action(self):
        target = None
        if any(isinstance(instance, SosnowskyHogweed) for instance in self._world.getOrganisms()):
            target = self.pathfind()
        if target is None:
            super().action()
            return
        self.move(target)
