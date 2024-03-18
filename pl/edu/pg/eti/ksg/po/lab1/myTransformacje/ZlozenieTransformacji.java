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