package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class Schronisko extends Atrakcja {

    public Schronisko(String miejscowosc) {
        super(10);
    }

    @Override
    public String getNazwa() {
        return "Schronisko";
    }

}
