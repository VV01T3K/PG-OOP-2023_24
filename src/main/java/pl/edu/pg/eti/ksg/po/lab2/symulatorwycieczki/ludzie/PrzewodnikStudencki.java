package pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wycieczka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Atrakcja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wedrowka;

import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.DrewnianaCerkiew;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.GestyLas;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.Panorama;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.Schronisko;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.ElektrowniaWodna;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.Tory;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.PoleBarszczuSosnowskiego;

/**
 *
 * @author TB
 */
public class PrzewodnikStudencki extends Student {

    public PrzewodnikStudencki(String imie, String nazwisko, Plec plec) {
        super(imie, nazwisko, plec, 5.0);
    }

    @Override
    public void opiszWycieczke(Wycieczka wycieczka) {
        mow("Szanowna grupo, proszę o uwagę. Teraz opowiem Wam o wycieczce.");
        super.opiszWycieczke(wycieczka);
    }

    @Override
    public int getUmiejetnosciNawigacyjne() {
        return 4;
    }

    @Override
    public void reagujNaAtrakcje(Atrakcja a, double czas) {
        if (a instanceof DrewnianaCerkiew) {
            DrewnianaCerkiew cerkiewka = (DrewnianaCerkiew) a;
            mow("To jest drewniana cerkiew w miejcowości " + cerkiewka.getMiejscowosc()
                    + ". Wiele taki można spotkać w Beskidach. Po mojej lewej widać wieżę o kontrukcji słupowo ramowej ...");
            regeneruj(czas);
        } else if (a instanceof Panorama) {
            mow("Tutaj mamy bardzo ładny widok na sąsiednie pasmo górskie. Od lewej widzimy ...");
            regeneruj(czas);
        } else if (a instanceof Schronisko) {
            mow("Witajcie w schronisku. To jest miejsce, gdzie można odpocząć, zjeść i napić się ...");
            regeneruj(czas);
        } else if (a instanceof ElektrowniaWodna) {
            mow("To jest elektrownia wodna. Woda z gór jest zbierana w zbiornikach, a następnie ...");
            regeneruj(czas);
        } else {
            super.reagujNaAtrakcje(a, czas);
        }
    }

    @Override
    public void reagujNaWedrowke(Wedrowka w, double czas) {
        if (w instanceof GestyLas) {
            mow("Tutaj mamy do czynienia z gęstym lasem. Warto zwrócić uwagę na ...");
            regeneruj(czas);
        } else if (w instanceof Tory) {
            mow("Tutaj mamy do czynienia z torami kolejowymi. Warto zwrócić uwagę na ...");
            regeneruj(czas);
        } else if (w instanceof PoleBarszczuSosnowskiego) {
            mow("Przed nami barszcz Sosnowskiego, roślina tak niebezpieczna, że nawet Chuck Norris boi się jej dotknąć.");
            regeneruj(czas);
        } else {
            super.reagujNaWedrowke(w, czas);
        }
    }

}
