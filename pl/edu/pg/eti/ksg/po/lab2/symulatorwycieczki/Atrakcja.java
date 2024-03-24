package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki;

public abstract class Atrakcja implements ElementWycieczki {
    private double czasZwiedzaniaH;

    public Atrakcja(double czasZwiedzaniaH) {
        this.czasZwiedzaniaH = czasZwiedzaniaH;
    }

    public double getCzasZwiedzaniaH() {
        return czasZwiedzaniaH;
    }

}