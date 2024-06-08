from .Animal import Animal
from Simulator.Organisms.Organism import Type
from Simulator.GlobalSettings import GlobalSettings
from Utils.DynamicDirections import DynamicDirections


class Human(Animal):
    def __init__(self, world, json=None):
        from Simulator.Abilities.Immortality import Immortality
        super().__init__(5, 4, world, Type.HUMAN, json)
        if (json is None):
            self.immortality = Immortality(5, 5)
        else:
            self.immortality = Immortality(
                json["ability_cooldown"], json["immortality_left"], 5, 5)
            if (json["immortality_left"] > 0 or json["ability_cooldown"] == 0):
                self.immortality.use()
        self.nextMove = DynamicDirections.get("SELF")

    def construct(self):
        return Human(self.world)

    def action(self):
        if (GlobalSettings.HUMAN_AI):
            self.immortality.use()
            self.immortality.update()
            super().action()
            return
        if (self.nextMove == DynamicDirections.get("SELF")):
            return
        if (self.immortality.checkToggle()):
            self.immortality.use()
            self.immortality.flipToggle()
        self.immortality.update()
        self.move(self.nextMove)
        self.nextMove = DynamicDirections.get("SELF")

    def collision(self, other):
        if (self.immortality.isActive()):
            self.immortality.effect(self, other)
            return
        else:
            super().collision(other)

    def collisionReaction(self, other):
        if (self.immortality.isActive()):
            self.immortality.effect(self, other)
            return True
        else:
            return False

    def setNextMove(self, direction):
        self.nextMove = direction

    def toggleImmortality(self):
        if (self.immortality.isReady() and not self.immortality.isActive()):
            self.immortality.flipToggle()

    def getNextMove(self):
        return self.nextMove

    def getAbilityInfo(self):
        if (self.immortality.isActive()):
            return f"{self.immortality.getDuration()} turns left"
        if (not self.immortality.isReady()):
            return f"{self.immortality.getCooldown()} turns of cooldown left"
        if (self.immortality.checkToggle()):
            return "Using next turn"
        return "Ready to use"

    def die(self):
        if (self.immortality.isActive()):
            self.immortality.effect(self)
        else:
            super().die()

    def toJson(self):
        json = super().toJson()
        json["ability_cooldown"] = self.immortality.getCooldown()
        json["immortality_left"] = self.immortality.getDuration()
        return json
