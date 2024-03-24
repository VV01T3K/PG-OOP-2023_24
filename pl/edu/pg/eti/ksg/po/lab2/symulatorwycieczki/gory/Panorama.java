package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class Panorama extends Atrakcja {

    public Panorama() {
        super(1 / 6f);
    }

    @Override
    public String getNazwa() {
        return "Panorama";
    }

}
