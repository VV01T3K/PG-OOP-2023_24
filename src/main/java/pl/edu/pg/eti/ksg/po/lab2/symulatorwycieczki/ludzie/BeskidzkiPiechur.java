package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.DrewnianaCerkiew;

public class BeskidzkiPiechur extends Czlowiek {
    public BeskidzkiPiechur(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 3.5, 20, 20);
    }

    @Override
    public void reagujNaAtrakcje(Atrakcja a, double czas) {
        if (a instanceof DrewnianaCerkiew) {
            mow("O drewniana cerkiew! Dobrze że nie jest kamienna, bo bym się zastanawiał czy to nie jest kościół.");
            regeneruj(czas * 2);
        } else
            super.reagujNaAtrakcje(a, czas);
    }

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 3;
    }
}
