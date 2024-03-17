package pl.edu.pg.eti.ksg.po.lab1.transformacje;

import pl.edu.pg.eti.ksg.po.lab1.B;

public class Punkt {
    private final double x, y;

    public Punkt(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof B) {
            Punkt other = (Punkt) obj;
            return x == other.x && y == other.y;
        }
        return false;
    }

    @Override
    public int hashCode() {
        return 60 * Double.hashCode(x) + 6 * Double.hashCode(y);
    }

    @Override
    public String toString() {
        return "Punkt(" + x + ", " + y + ")";
    }

    /**
     * Początek układu współrzędnych.
     * W tym miejscu słowo kluczowe final oznacza, że statyczne
     * pole klasy Punkt nie może zostać zmienione.
     * Dotyczy to jednak samej referencji, a nie obiektu, na który
     * wskazuje.
     */
    public static final Punkt O = new Punkt(0, 0);

    /**
     * Punkt (1,0) w układzie współrzędnych
     */
    public static final Punkt E_X = new Punkt(1, 0);

    /**
     * Punkt (0,1) w układzie współrzędnych
     */
    public static final Punkt E_Y = new Punkt(0, 1);
}