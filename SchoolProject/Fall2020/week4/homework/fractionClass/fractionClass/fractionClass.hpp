//
//  fractionClass.hpp
//  fractionClass
//
//  Created by Garret Wasden on 9/16/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#ifndef fractionClass_hpp
#define fractionClass_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Fraction{
private:
    long numerator;
    long denominator;
    
    void reduce();
//    long gcd();
    
public:
    Fraction();
    Fraction(long n, long d);
    long getNumerator();
    long getDenominator();
    Fraction plus(Fraction rhs);
    Fraction minus(Fraction rhs);
    Fraction times(Fraction rhs);
    Fraction dividedBy(Fraction rhs);
    Fraction reciprocal();
    string toString();
    double toDouble();
    
//lab overloads
    
    Fraction& operator+=(Fraction rhs);
    Fraction& operator+(Fraction rhs);
    Fraction& operator-=(Fraction rhs);
    Fraction& operator-(Fraction rhs);
    Fraction& operator*=(Fraction rhs);
    Fraction& operator*(Fraction rhs);
    Fraction& operator/=(Fraction rhs);
    Fraction& operator/(Fraction rhs);
    bool operator==(Fraction rhs);
    bool operator!=(Fraction rhs);
    bool operator<=(Fraction rhs);
    bool operator<(Fraction rhs);
    bool operator>=(Fraction rhs);
    bool operator>(Fraction rhs);
    
};

void Test(std::string message, std::string expected, std::string result);

void Test(std::string message, double expected, double result);


#endif /* fractionClass_hpp */
