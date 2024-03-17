package pl.edu.pg.eti.ksg.po.lab1.myTransformacje;

import pl.edu.pg.eti.ksg.po.lab1.transformacje.Transformacja;
import pl.edu.pg.eti.ksg.po.lab1.transformacje.Punkt;
import pl.edu.pg.eti.ksg.po.lab1.transformacje.BrakTransformacjiOdwrotnejException;

import java.lang.Math;

public class Obrot implements Transformacja {

    private final double angle;

    public Obrot(double angle) {
        this.angle = angle;
    }

    @Override
    public Transformacja getTransformacjaOdwrotna() throws BrakTransformacjiOdwrotnejException {
        return new Obrot(-angle);
    }

    @Override
    public Punkt transformuj(Punkt p) {
        double rad = Math.toRadians(angle);
        double x = Math.round(p.getX() * Math.cos(rad) - p.getY() * Math.sin(rad));
        double y = Math.round(p.getX() * Math.sin(rad) + p.getY() * Math.cos(rad));
        return new Punkt(x, y);
    }

    public double getAngle() {
        return angle;
    }

    @Override
    public String toString() {
        return "Obrot o kąt: " + angle;
    }

}
