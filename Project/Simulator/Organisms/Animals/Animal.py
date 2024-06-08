import json

from abc import ABC, abstractmethod
from tkinter import N

from Simulator.Tile import Tile
from Simulator.Organisms.Organism import Organism
from Simulator.GlobalSettings import GlobalSettings
from Utils.DynamicDirections import DynamicDirections


class Animal(Organism, ABC):
    def __init__(self, power, initiative, world, type, json=None):
        super().__init__(type, power, initiative, world, json)
        self._oldTile = None
        if json is not None:
            index = json["old_tile_index"]
            self._oldTile = world.getTile(index) if index != -1 else None

    def move(self, newTileOrDirection):
        if (newTileOrDirection == None):
            return
        if isinstance(newTileOrDirection, DynamicDirections):
            newTile = self._tile.getNeighbour(newTileOrDirection)
        else:
            newTile = newTileOrDirection
        if (newTile == None):
            return
        self._oldTile = self._tile
        self._tile = newTile
        self._tile.placeOrganism(self)
        if self._oldTile is not None:
            self._oldTile.removeOrganism(self)

    def undoMove(self):
        if self._oldTile is None:
            return
        self._oldTile.placeOrganism(self)
        self._tile.removeOrganism(self)
        self._tile = self._oldTile
        self._oldTile = None

    def action(self):
        self.move(self._tile.getRandomNeighbour())

    def getBreedCooldown(self):
        return self._reproductionCooldown

    def setBreedCooldown(self, value):
        self._reproductionCooldown = value

    def collision(self, other: Organism):
        if other.collisionReaction(self):
            return

        if type(self) == type(other):
            self.undoMove()
            if not GlobalSettings.AI_REPRODUCE:
                return
            other.skipTurn()
            if self.getBreedCooldown() > 0:
                return
            tile = other.getTile()
            new_Tile = tile.getRandomFreeNeighbour() if tile is not None else None
            if new_Tile is None:
                return
            new_animal = self.construct()
            if (new_animal is None):
                raise Exception(
                    "construct method must return an instance of Animal")
            new_animal.skipTurn()
            self.setBreedCooldown(5)
            other.setBreedCooldown(5)
            new_animal.setBreedCooldown(10)
            self._world.addOrganism(new_animal, new_Tile)

            self._world.addLog(
                f"{self.getSymbol()} and {other.getSymbol()} bred a new {new_animal.getSymbol()}!")
        elif self.getPower() > other.getPower():
            other.die()
            self._world.addLog(
                f"{self.getSymbol()} killed {other.getSymbol()}!")
        else:
            self.die()
            self._world.addLog(
                f"{self.getSymbol()} was killed by {other.getSymbol()}!")

    def collisionReaction(self, other):
        return False

    @abstractmethod
    def construct(self):
        pass

    def toJson(self):
        json = super().toJson()
        json["old_tile_index"] = self._oldTile.INDEX if self._oldTile is not None else -1
        return json
