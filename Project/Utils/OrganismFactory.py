from Simulator.Organisms.Organism import Type
from Simulator.Organisms.Animals import *
from Simulator.Organisms.Plants import *


class OrganismFactory:
    def __init__(self, world):
        self.__world = world

    def create(self, json):
        type = Type.getTypeByInt(json["type"])
        match type:
            case Type.ANTELOPE:
                return Antelope(self.__world, json)
            case Type.CYBER_SHEEP:
                return CyberSheep(self.__world, json)
            case Type.FOX:
                return Fox(self.__world, json)
            case Type.HUMAN:
                return Human(self.__world, json)
            case Type.SHEEP:
                return Sheep(self.__world, json)
            case Type.TURTLE:
                return Turtle(self.__world, json)
            case Type.WOLF:
                return Wolf(self.__world, json)
            case Type.GRASS:
                return Grass(self.__world, json)
            case Type.GUARANA:
                return Guarana(self.__world, json)
            case Type.MILKWEED:
                return Milkweed(self.__world, json)
            case Type.SOSNOWSKY_HOGWEED:
                return SosnowskyHogweed(self.__world, json)
            case Type.BELLADONNA:
                return Belladonna(self.__world, json)
            case _:
                raise Exception("Invalid type")

    def createFromType(self, type):
        match type:
            case Type.ANTELOPE:
                return Antelope(self.__world)
            case Type.CYBER_SHEEP:
                return CyberSheep(self.__world)
            case Type.FOX:
                return Fox(self.__world)
            case Type.HUMAN:
                return Human(self.__world)
            case Type.SHEEP:
                return Sheep(self.__world)
            case Type.TURTLE:
                return Turtle(self.__world)
            case Type.WOLF:
                return Wolf(self.__world)
            case Type.GRASS:
                return Grass(self.__world)
            case Type.GUARANA:
                return Guarana(self.__world)
            case Type.MILKWEED:
                return Milkweed(self.__world)
            case Type.SOSNOWSKY_HOGWEED:
                return SosnowskyHogweed(self.__world)
            case Type.BELLADONNA:
                return Belladonna(self.__world)
            case _:
                raise Exception("Invalid type")
