package pl.edu.pg.eti.ksg.po.lab1.myTransformacje;

import pl.edu.pg.eti.ksg.po.lab1.transformacje.Transformacja;
import pl.edu.pg.eti.ksg.po.lab1.transformacje.Punkt;
import pl.edu.pg.eti.ksg.po.lab1.transformacje.BrakTransformacjiOdwrotnejException;

public class ZlozenieTransformacji implements Transformacja {

    private Transformacja[] transformacje;

    public ZlozenieTransformacji(Transformacja... transformacje) {
        this.transformacje = transformacje;
    }

    @Override
    public Transformacja getTransformacjaOdwrotna() throws BrakTransformacjiOdwrotnejException {
        Transformacja[] transformacjeOdwrotne = new Transformacja[transformacje.length];
        for (int i = 0; i < transformacje.length; i++) {
            transformacjeOdwrotne[i] = transformacje[transformacje.length - 1 - i].getTransformacjaOdwrotna();
        }
        return new ZlozenieTransformacji(transformacjeOdwrotne);
    }

    @Override
    public Punkt transformuj(Punkt p) {
        for (Transformacja transformacja : transformacje) {
            p = transformacja.transformuj(p);
        }
        return p;
    }

    public Transformacja[] getTransformacje() {
        return transformacje;
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder("Zlozenie transformacji:");
        for (Transformacja transformacja : transformacje) {
            str.append("\n ->").append(transformacja.toString());
        }
        return str.toString();
    }

}

// public static void main(String[] args) {
// Punkt p = new Punkt(1, 1);
// Transformacja t1 = new Translacja(1, 1);
// Transformacja t2 = new Skalowanie(2, 2);
// Transformacja t3 = new Obrot(Math.PI / 2);
// Transformacja t4 = new Skalowanie(0.5, 0.5);
// Transformacja t5 = new Translacja(-1, -1);
// Transformacja zlozenie = new ZlozenieTransformacji(t1, t2, t3, t4, t5);
// System.out.println(zlozenie);
// System.out.println(zlozenie.transformuj(p));
// }