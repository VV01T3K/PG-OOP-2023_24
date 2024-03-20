package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

public class PoleBarszczuSosnowskiego extends Wedrowka {

    public PoleBarszczuSosnowskiego(double odleglosc) {
        super(odleglosc);
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc) {
        return 0.75f * predkosc;
    }

    @Override
    public int getTrudnoscNawigacyjna() {
        return 3;
    }

    @Override
    public String getNazwa() {
        return "Pole Barszczu Sosnowskiego";
    }

}
