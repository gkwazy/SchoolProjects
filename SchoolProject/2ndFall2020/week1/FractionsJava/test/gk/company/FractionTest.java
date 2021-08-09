package gk.company;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class FractionTest {

    @Test
    void Fraction() {
        Fraction fraction = new Fraction (10,20);
        assertEquals(1,fraction.numerator);
    }
    @Test
    void FractionZero() {
        try{
            Fraction fraction = new Fraction (10,0);
            assert(false);
        }
        catch(Exception e){
            System.out.println("test Passed");
        }

    }

    @Test
    void plus() {
        Fraction fraction = new Fraction (10,20);
        Fraction fractionTwo = new Fraction(1,4);
        Fraction answer = new Fraction(3,4);
        assertEquals("3/4",fraction.plus(fractionTwo).toString());
    }

    @Test
    void minus() {
        Fraction fraction = new Fraction (10,20);
        Fraction fractionTwo = new Fraction(1,4);
        assertEquals("1/4",fraction.minus(fractionTwo).toString());
    }

    @Test
    void times() {
        Fraction fraction = new Fraction (10,20);
        Fraction fractionTwo = new Fraction(1,4);
        assertEquals("1/8",fraction.times(fractionTwo).toString());
    }

    @Test
    void dividedBy() {
        Fraction fraction = new Fraction (10,20);
        Fraction fractionTwo = new Fraction(1,4);
        assertEquals("2/1",fraction.dividedBy(fractionTwo).toString());
    }

    @Test
    void reciprocal() {
        Fraction fraction = new Fraction (10,20);
        assertEquals("2/1",fraction.reciprocal().toString());
    }

    @Test
    void toDouble() {
        Fraction fraction = new Fraction (1,3);
        assertEquals(0.333,fraction.toDouble(),0.001);
    }

    @Test
    void compareTo() {
        Fraction first = new Fraction (2,3);
        Fraction second = new Fraction(1,3);
        Fraction third = new Fraction ( 9, 27);

        assertEquals(1,first.compareTo(second),0.001);
        assertEquals(0,second.compareTo(second),0.001);
        assertEquals(-1,second.compareTo(first),0.001);
    }


}