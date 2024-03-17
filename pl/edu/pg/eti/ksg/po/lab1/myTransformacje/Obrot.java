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
        double x = p.getX();
        double y = p.getY();
        double x1 = x * Math.cos(angle) - y * Math.sin(angle);
        double y1 = x * Math.sin(angle) + y * Math.cos(angle);
        return new Punkt(x1, y1);
    }

    public double getAngle() {
        return angle;
    }

    @Override
    public String toString() {
        return "Obrot o angle " + angle;
    }

}
