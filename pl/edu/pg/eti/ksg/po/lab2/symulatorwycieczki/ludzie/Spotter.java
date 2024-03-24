package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.Tory;

public class Spotter extends Czlowiek {
    public Spotter(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 4.5);
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas) {
        if (w instanceof Tory) {
            mow("O tory! Czy to nie jest miejsce gdzie można zobaczyć pociągi?");
            regeneruj(czas / 2);
        } else
            super.reagujNaWedrowke(w, czas);
    }

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 2;
    }
}
