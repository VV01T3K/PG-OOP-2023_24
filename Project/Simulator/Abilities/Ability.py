from abc import ABC, abstractmethod
from Simulator.Organisms.Organism import Organism
from typing import Optional


class Ability(ABC):
    def __init__(self, cooldown, duration, default_cooldown=-1, default_duration=-1):
        if (default_cooldown == -1) or (default_duration == -1):
            self.default_cooldown = cooldown
            self.default_duration = duration + 1
        else:
            self.default_cooldown = default_cooldown
            self.default_duration = default_duration
            self.cooldown = cooldown
            self.duration = duration
        self.toggle = False

    def isReady(self):
        return self.cooldown == 0

    def isActive(self):
        return self.duration > 0

    def getCooldown(self):
        return self.cooldown

    def getDuration(self):
        return self.duration

    def checkToggle(self):
        return self.toggle

    def flipToggle(self):
        self.toggle = not self.toggle

    def use(self):
        if (self.isReady() and not self.isActive()):
            self.cooldown = self.default_cooldown
            self.duration = self.default_duration

    def update(self):
        if self.duration > 0:
            self.duration -= 1
        elif self.cooldown > 0:
            self.cooldown -= 1

    @abstractmethod
    def effect(self, user: Organism, other: Optional[Organism] = None):
        pass
