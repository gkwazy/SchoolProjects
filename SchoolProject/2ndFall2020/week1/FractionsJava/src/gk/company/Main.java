package gk.company;

import java.util.ArrayList;
import java.util.Collections;

public class Main {

    public static void main(String[] args) {
        Fraction first = new Fraction (10,20);
        Fraction second = new Fraction(1,3);
        Fraction third = new Fraction ( 9, 27);
        Fraction total = new Fraction();

        ArrayList<Fraction> myList = new ArrayList<Fraction>();
        myList.add(second);
        myList.add(third);
        myList.add(first);


        for(Fraction fraction: myList){
            System.out.println(fraction);
        }
        System.out.println(",");

        Collections.sort(myList);

        for(Fraction fraction: myList){
            System.out.println(fraction);
        }

    }
}
