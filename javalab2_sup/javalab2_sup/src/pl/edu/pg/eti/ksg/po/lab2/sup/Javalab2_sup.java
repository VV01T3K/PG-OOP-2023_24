package pl.edu.pg.eti.ksg.po.lab2.sup;

import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author TB
 */
public class Javalab2_sup {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int a = 5;
        double b = 3.14;
        ZwyklaKlasa instancjaA = new ZwyklaKlasa();
        ZwyklaKlasa instancjaB = new ZwyklaKlasa();
        
        List<SluchaczZdarzen> listaSluchaczy = new LinkedList<>();
        
        listaSluchaczy.add(instancjaA.klasaWewnetrzna());
        listaSluchaczy.add(instancjaA.statycznaKlasaWewnetrzna());
        listaSluchaczy.add(instancjaA.klasaAnonimowa());
        
        
        /**
         * Wyrażenia lambda wprowadzono w Javie 8. Można przyjąć,
         * że jest to skrócona wersja klasy anonimowej 
         * dla interfejsu oznaczonego andotacją
         * @FunctionalInterface
         */
        listaSluchaczy.add((int p, String n) -> {
                System.out.println("Wyrażenie Lambda obsługuje zdarzenie "+n
                    +" o priorytecie "+p);
                System.out.println("Wartosci pól:");
                System.out.println("wartość a z funkcji main: "+ a);
                System.out.println("wartość b z funkcji main: "+ b);
        });
        
        /**
         * Wprowadzone w Javie 8. Pozwala przekonwertować metodę obiektu na
         * klasę implementującą interfejs funkcjonalny.
         */
        listaSluchaczy.add(instancjaB::zwyklaMetoda);
        
        /**
         * Wprowadzone w Javie 8. Pozwala przekonwertować metodę statyczną na
         * klasę implementującą interfejs funkcjonalny
         */
        listaSluchaczy.add(ZwyklaKlasa::zwyklaStatycznaMetoda);
        
        String nazwa = "Test Interfejsów";
        int priorytet = 8;
        for(SluchaczZdarzen sl : listaSluchaczy)
        {
            sl.wystapiloZdarzenie(priorytet, nazwa);
        }
        
    }
    
}
