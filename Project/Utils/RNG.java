package Utils;

import java.util.Random;

public class RNG {
    private static final Random gen = new Random();

    private RNG() {
    }

    public static int roll(long min, long max) {
        return (int) (min + (long) (gen.nextDouble() * (max - min)));
    }
}