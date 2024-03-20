package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.PoleBarszczuSosnowskiego;

public class YouTuber extends Czlowiek {
    public YouTuber(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 3, 30, 30);
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas) {
        if (w instanceof PoleBarszczuSosnowskiego) {
            mow("Lepiej będę uważał, bo znowu będą mówić o poparzeniach w RMF FM ...");
            aktualizujZmeczenie(czas * 1.2);
        } else
            super.reagujNaWedrowke(w, czas);
    }

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 1;
    }
}
