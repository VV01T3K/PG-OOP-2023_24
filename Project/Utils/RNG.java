package Utils;

import java.util.Random;

public class RNG {
    private static RNG instance;
    private Random gen;

    private RNG() {
        this.gen = new Random();
    }

    public static RNG getInstance() {
        if (instance == null) {
            instance = new RNG();
        }
        return instance;
    }

    public int roll(long min, long max) {
        return (int) (min + (long) (gen.nextDouble() * (max - min)));
    }
}