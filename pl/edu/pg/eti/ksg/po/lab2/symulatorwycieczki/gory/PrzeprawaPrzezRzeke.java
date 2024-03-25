package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

public class PrzeprawaPrzezRzeke extends Wedrowka {

    public PrzeprawaPrzezRzeke(double odleglosc) {
        super(odleglosc);
    }

    @Override
    public double modyfikujPredkoscGrupy(double predkosc) {
        return 0.3f * predkosc;
    }

    @Override
    public int getTrudnoscNawigacyjna() {
        return 4;
    }

    @Override
    public String getNazwa() {
        return "Przeprawa przez rzeke";
    }

}
