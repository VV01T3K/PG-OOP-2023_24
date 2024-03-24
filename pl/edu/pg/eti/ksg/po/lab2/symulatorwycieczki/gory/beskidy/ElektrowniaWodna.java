package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;

public class ElektrowniaWodna extends Atrakcja {

    private String nazwaRzeki;

    public ElektrowniaWodna(String nazwaRzeki) {
        super(1);
        this.nazwaRzeki = nazwaRzeki;
    }

    public String getNazwaRzeki() {
        return nazwaRzeki;
    }

    @Override
    public String getNazwa() {
        return "Elektrownia Wodna";
    }

}
