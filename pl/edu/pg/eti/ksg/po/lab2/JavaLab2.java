package pl.edu.pg.eti.ksg.po.lab2;

import java.util.HashSet;
import java.util.Set;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Grupa;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.SymulatorWycieczki;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Uczestnik;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.Wycieczka;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.Droga;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.Las;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.Czlowiek;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.PrzewodnikStudencki;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.Student;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.StudentKSG;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.DrewnianaCerkiew;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.GestyLas;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.Panorama;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.PrzeprawaPrzezRzeke;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.Schronisko;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.ElektrowniaWodna;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.Tory;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.gory.beskidy.PoleBarszczuSosnowskiego;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.CzlowiekZKontuzja;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.Spotter;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.YouTuber;
import pl.edu.pg.eti.ksg.po.lab2.symulatorwycieczki.ludzie.BeskidzkiPiechur;

/**
 *
 * @author TB
 */
public class JavaLab2 {
    public static void main(String[] args) {
        // Wycieczka w = doDydiowki();
        // Wycieczka w = doSchroniska();
        Wycieczka w = PiwnicznaZdrójToRytro();

        PrzewodnikStudencki przewodnik = new PrzewodnikStudencki("Stefan", "Długonogi", Czlowiek.Plec.MEZCZYZNA);
        Set<Uczestnik> uczestnicy = new HashSet<>();
        uczestnicy.add(new Student("Ada", "Lovelace", Czlowiek.Plec.KOBIETA));
        uczestnicy.add(new StudentKSG("Piotr", "Teledetekcyjny", Czlowiek.Plec.MEZCZYZNA));
        uczestnicy.add(new CzlowiekZKontuzja("Jan", "Kowalski", Czlowiek.Plec.MEZCZYZNA));
        uczestnicy.add(new YouTuber("Jacek", "Makarewicz", Czlowiek.Plec.MEZCZYZNA));
        uczestnicy.add(new BeskidzkiPiechur("Krzysztof", "Krawczyk", Czlowiek.Plec.MEZCZYZNA));
        uczestnicy.add(new Spotter("Marek", "Markowski", Czlowiek.Plec.MEZCZYZNA));

        Grupa g = new Grupa(przewodnik, uczestnicy);

        SymulatorWycieczki symulator = new SymulatorWycieczki(g, w);

        symulator.dodajSluchaczaPostepow((elementWycieczki, lp, liczbaElementow) -> {
            System.out.println("Aktualizacja postępu: " + (lp + 1) + "/" + liczbaElementow);
        });

        symulator.symuluj();
    }

    public static Wycieczka doDydiowki() {
        Wycieczka ret = new Wycieczka("Do Dydiówki");
        ret.dodajElementWycieczki(new Droga(1.0));
        ret.dodajElementWycieczki(new DrewnianaCerkiew("Smolnik"));
        ret.dodajElementWycieczki(new Droga(4.0));
        // ret.dodajElementWycieczki(new PrzeprawaPrzezRzeke(1.0));
        ret.dodajElementWycieczki(new GestyLas(2.0));
        ret.dodajElementWycieczki(new Las(2.0));
        ret.dodajElementWycieczki(new Droga(5.0));

        return ret;
    }

    public static Wycieczka doSchroniska() {
        Wycieczka ret = new Wycieczka("Do schroniska");
        ret.dodajElementWycieczki(new Droga(4.0));
        ret.dodajElementWycieczki(new PoleBarszczuSosnowskiego(2));
        ret.dodajElementWycieczki(new ElektrowniaWodna("San"));
        ret.dodajElementWycieczki(new Droga(5.0));
        ret.dodajElementWycieczki(new Tory(3.0));
        ret.dodajElementWycieczki(new PoleBarszczuSosnowskiego(3.0));
        ret.dodajElementWycieczki(new Panorama());
        ret.dodajElementWycieczki(new Droga(8.0));
        ret.dodajElementWycieczki(new Schronisko("Klimczok"));

        return ret;
    }

    public static Wycieczka PiwnicznaZdrójToRytro() {
        Wycieczka ret = new Wycieczka("Rytro, Zazamcze");
        ret.dodajElementWycieczki(new Droga(1.0));
        ret.dodajElementWycieczki(new Tory(1.0));
        ret.dodajElementWycieczki(new Droga(5.0));
        ret.dodajElementWycieczki(new Las(3));
        ret.dodajElementWycieczki(new GestyLas(3));
        ret.dodajElementWycieczki(new PoleBarszczuSosnowskiego(0.5));
        ret.dodajElementWycieczki(new Schronisko("Cyrla"));
        ret.dodajElementWycieczki(new Droga(3.0));
        ret.dodajElementWycieczki(new PrzeprawaPrzezRzeke(0.5));
        ret.dodajElementWycieczki(new Droga(0.5));
        ret.dodajElementWycieczki(new Panorama());

        return ret;
    }

}
