package pl.edu.pg.eti.ksg.po.lab1.transformacje;

public class Main1 {
    public static void main(String[] args) {
        Punkt p1 = new Punkt(1, 2);
        Punkt p2 = new Punkt(1, 2);
        Punkt p3 = new Punkt(2, 3);

        System.out.println("p1: " + p1);
        System.out.println("p2: " + p2);
        System.out.println("p3: " + p3);

        System.out.println("p1?p2: " + p1.equals(p2));
        System.out.println("p1?p3: " + p1.equals(p3));

        System.out.println("p1-hash: " + p1.hashCode());
        System.out.println("p2-hash: " + p2.hashCode());

        System.out.println("p1.x p1y: " + p1.getX() + " " + p1.getY());

        // System.out.println(Punkt.O);
        // System.out.println(Punkt.E_X);
        // System.out.println(Punkt.E_Y);

    }
}