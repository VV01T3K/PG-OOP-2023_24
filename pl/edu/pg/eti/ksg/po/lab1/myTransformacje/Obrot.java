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
        double radianAngle = Math.toRadians(angle);
        double x = Math.round(p.getX() * Math.cos(radianAngle) - p.getY() * Math.sin(radianAngle));
        double y = Math.round(p.getX() * Math.sin(radianAngle) + p.getY() * Math.cos(radianAngle));
        return new Punkt(x, y);
    }

    public double getAngle() {
        return angle;
    }

    @Override
    public String toString() {
        return "Obrot o angle " + angle;
    }

}
