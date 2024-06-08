from Simulator.Organisms.Organism import Type
from Simulator.Organisms.Animals import *
from Simulator.Organisms.Plants import *


class OrganismFactory:
    def __init__(self, world):
        self.world = world

    def create(self, json):
        type = Type.getTypeByInt(json["type"])
        match type:
            case Type.ANTELOPE:
                return Antelope(self.world, json)
            case Type.CYBER_SHEEP:
                return CyberSheep(self.world, json)
            case Type.FOX:
                return Fox(self.world, json)
            case Type.HUMAN:
                return Human(self.world, json)
            case Type.SHEEP:
                return Sheep(self.world, json)                
            case Type.TURTLE:
                return Turtle(self.world, json)
            case Type.WOLF:
                return Wolf(self.world, json)
            case Type.GRASS:
                return Grass(self.world, json)
            case Type.GUARANA:
                return Guarana(self.world, json)
            case Type.MILKWEED:
                return Milkweed(self.world, json)                
            case Type.SOSNOWSKY_HOGWEED:
                return SosnowskyHogweed(self.world, json)
            case Type.WOLF_BERRIES:
                return WolfBerries(self.world, json)
            case _:
                raise Exception("Invalid type")

    def createFromType(self, type):
        match type:
            case Type.ANTELOPE:
                return Antelope(self.world)
            case Type.CYBER_SHEEP:
                return CyberSheep(self.world)
            case Type.FOX:
                return Fox(self.world)
            case Type.HUMAN:
                return Human(self.world)
            case Type.SHEEP:
                return Sheep(self.world)                
            case Type.TURTLE:
                return Turtle(self.world)
            case Type.WOLF:
                return Wolf(self.world)
            case Type.GRASS:
                return Grass(self.world)
            case Type.GUARANA:
                return Guarana(self.world)
            case Type.MILKWEED:
                return Milkweed(self.world)                
            case Type.SOSNOWSKY_HOGWEED:
                return SosnowskyHogweed(self.world)
            case Type.WOLF_BERRIES:
                return WolfBerries(self.world)
            case _:
                raise Exception("Invalid type")
