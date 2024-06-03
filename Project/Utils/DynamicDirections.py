class DynamicDirections:
    instances = {}
    next_ordinal = 0

    def __init__(self, name):
        self.name = name
        self.ordinal_value = DynamicDirections.next_ordinal
        DynamicDirections.next_ordinal += 1

    @classmethod
    def addInstance(cls, name):
        instance = DynamicDirections(name)
        cls.instances[name] = instance
        return instance

    @classmethod
    def get(cls, name):
        return cls.instances.get(name)

    def ordinal(self):
        return self.ordinal_value

    def __str__(self):
        return self.name

    @classmethod
    def values(cls):
        return list(cls.instances.values())

    @classmethod
    def clear(cls):
        cls.instances.clear()
        cls.next_ordinal = 0
