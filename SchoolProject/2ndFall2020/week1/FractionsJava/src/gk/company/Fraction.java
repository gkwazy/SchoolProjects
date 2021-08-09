package gk.company;

public class Fraction implements Comparable<Fraction> {
    long numerator;
    long denominator;

    public Fraction() {
        numerator = 0;
        denominator = 1;
    }
    public Fraction(long n, long d){
        if( d == 0){
            throw new ArithmeticException("Demoninator can not be 0");
        }
        numerator = n;
        denominator = d;
        //reducing the fraction
        long gcd = GCD(numerator, denominator);
        numerator = numerator/gcd;
        denominator = denominator/gcd;
    }

    private long GCD(long n, long d){
        long gcd = numerator;
        long remainder = denominator;
        while(remainder != 0) {
            long temp = remainder;
            remainder = gcd % remainder;
            gcd = temp;
        }
        return gcd;
    }

    private Fraction reduce(Fraction rhs){
        long gcd =  GCD(rhs.numerator, rhs.denominator);
        Fraction newFraction = new Fraction((rhs.numerator/gcd), (rhs.denominator/gcd));
        return newFraction;
    }

    public Fraction plus (Fraction rhs){
        long newDenominator = rhs.denominator * denominator;
        long newNumerator = (rhs.numerator * denominator) + (numerator * rhs.denominator);
        Fraction newFraction = new Fraction(newNumerator, newDenominator);
        return newFraction;
    }

    public Fraction minus (Fraction rhs){
        long newDenominator = rhs.denominator * denominator;
        long newNumerator = ((numerator * rhs.denominator) - (rhs.numerator * denominator));
        Fraction newFraction = new Fraction(newNumerator, newDenominator);
        return newFraction;
    }

    public Fraction times(Fraction rhs){
        long newDenominator = rhs.denominator * denominator;
        long newNumerator = (rhs.numerator * numerator) ;
        Fraction newFraction = new Fraction(newNumerator, newDenominator);
        return newFraction;
    }

    public Fraction dividedBy(Fraction rhs){
        long newDenominator = (denominator * rhs.numerator);
        long newNumerator = (numerator * rhs.denominator) ;
        Fraction newFraction = new Fraction(newNumerator, newDenominator);
        return newFraction;
    }

    public Fraction reciprocal(){
        Fraction newFraction = new Fraction(denominator, numerator);
        return newFraction;
    }

    public String toString(){
        String negative = "";
        if (numerator < 0 || denominator < 0 ){
            negative = "-";
        }
        String total = negative + Long.toString(numerator) + "/" + Long.toString(denominator);
        return total;
    }

    public double toDouble(){
        double total = (double) numerator/ (double) denominator;
        return total;
    }

    @Override
    public int compareTo(Fraction other) {
       double lhs = this.toDouble();
       double rhs = other.toDouble();
       if ((lhs-rhs) < 0) {
           return -1;
       }
        if ((lhs-rhs) == 0) {
            return 0;
        }
        return 1;
    }
}
