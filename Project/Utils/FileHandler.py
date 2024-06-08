import json
from pathlib import Path

from Simulator.World import World, HexWorld
from Utils.OrganismFactory import OrganismFactory


class FileHandler:
    @staticmethod
    def save_world(world: World, name: str, window_width: int, window_height: int):
        organisms = world.getOrganisms()
        if not organisms:
            return

        json_organisms = [organism.toJson() for organism in organisms]

        json_world = {
            "width": world.getWidth(),
            "height": world.getHeight(),
            "time": world.checkTime(),
            "hexagonal": isinstance(world, HexWorld),
            "window_width": window_width,
            "window_height": window_height
        }

        data = {
            "organisms": json_organisms,
            "world": json_world
        }

        with open(f"Project/Saves/{name}.json", "w") as file:
            json.dump(data, file)

    @staticmethod
    def listSaves():
        return [f.name for f in sorted(list(filter(lambda f: f.is_file(), list(Path("Project/Saves/").glob("*.json")))))]

    @staticmethod
    def loadWorld(name: str) -> World:
        with open(f"Project/Saves/{name}.json", "r") as file:
            data = json.load(file)

        world = None
        if data["world"]["hexagonal"]:
            world = HexWorld(data["world"]["width"], data["world"]["height"])
        else:
            world = World(data["world"]["width"], data["world"]["height"])
        world.setTime(data["world"]["time"])
        organisms = [OrganismFactory(world).create(organism)
                     for organism in data["organisms"]]
        world.setOrganisms(organisms)
        world.setHuman(world.findHuman())
        return world
