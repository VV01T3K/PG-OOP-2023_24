package Utils;

import java.util.HashMap;
import java.util.Map;

public class DynamicDirections {
    private static final Map<String, DynamicDirections> instances = new HashMap<>();
    private static int nextOrdinal = 0;
    private final String name;
    private final int ordinal;

    private DynamicDirections(String name) {
        this.name = name;
        this.ordinal = nextOrdinal++;
    }

    public static DynamicDirections addInstance(String name) {
        DynamicDirections instance = new DynamicDirections(name);
        instances.put(name, instance);
        return instance;
    }

    public static DynamicDirections get(String name) {
        return instances.get(name);
    }

    public int ordinal() {
        return ordinal;
    }

    @Override
    public String toString() {
        return name;
    }

    public static DynamicDirections[] values() {
        return instances.values().toArray(new DynamicDirections[0]);
    }

    public static void clear() {
        instances.clear();
        nextOrdinal = 0;
    }
}