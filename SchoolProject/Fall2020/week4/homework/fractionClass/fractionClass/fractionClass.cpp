//
//  fractionClass.cpp
//  fractionClass
//
//  Created by Garret Wasden on 9/16/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include "fractionClass.hpp"
#include <string>
using namespace std;

long gcd(long a, long b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

Fraction::Fraction(){
    numerator = 0;
    denominator = 1;
}

Fraction::Fraction(long n, long d){
    numerator = n;
    denominator = d;
    long tempgcd = gcd(numerator, denominator);
        numerator = numerator/tempgcd;
        denominator = denominator/tempgcd;
    if (denominator < 0){
        numerator = numerator * (long)-1;
        denominator = denominator * (long) -1;
    }
}

long Fraction::getNumerator(){
    return numerator;
}


long Fraction::getDenominator(){
    return denominator;
}

Fraction Fraction::plus(Fraction rhs){
    long newDenominator = rhs.denominator * denominator;
    long newNumerator = (rhs.numerator * denominator) + (numerator * rhs.denominator);
   return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::minus(Fraction rhs){
    long newDenominator = rhs.denominator * denominator;
    long newNumerator = ((numerator * rhs.denominator) - (rhs.numerator * denominator));
    return Fraction(newNumerator, newDenominator);
}
Fraction Fraction::times(Fraction rhs){
    long newDenominator = rhs.denominator * denominator;
    long newNumerator = (rhs.numerator * numerator) ;
    return Fraction(newNumerator, newDenominator);
}
Fraction Fraction::dividedBy(Fraction rhs){
    long newDenominator = (rhs.denominator * numerator);
    long newNumerator = (rhs.numerator * denominator) ;
    return Fraction(newNumerator, newDenominator);
}
Fraction Fraction::reciprocal(){
     return Fraction(denominator, numerator);
}

string Fraction::toString(){
    long newDenominator = denominator;
    long newNumerator = numerator;
    return to_string(newNumerator) + "/" + to_string(newDenominator);
}

double Fraction::toDouble(){
    return (double) numerator / (double) denominator;
}


//lab writing overloads for the operations.
Fraction& Fraction::operator+=(Fraction rhs){
    numerator = (rhs.numerator * denominator) + (numerator * rhs.denominator);
    denominator = rhs.denominator * denominator;
    Fraction temp(numerator, denominator);
    *this = temp;
    return *this;
}

Fraction& Fraction::operator+(Fraction rhs){
    *this = *this += rhs;
    return *this;
}

Fraction& Fraction::operator-=(Fraction rhs){
    numerator =  (numerator * rhs.denominator)-(rhs.numerator * denominator) ;
    denominator = rhs.denominator * denominator;
    Fraction temp(numerator, denominator);
    *this = temp;
    return *this;
}

Fraction& Fraction::operator-(Fraction rhs){
    *this = *this-=rhs;
    return *this;
}

Fraction& Fraction::operator*=(Fraction rhs){
     denominator = rhs.denominator * denominator;
     numerator = (rhs.numerator * numerator) ;
    *this = Fraction(numerator, denominator);
    return *this;
}

Fraction& Fraction::operator*(Fraction rhs){
    *this = *this*=rhs;
    return *this;
}

Fraction& Fraction::operator/=(Fraction rhs){
    long tempNumerator = numerator;
    numerator = (rhs.denominator * tempNumerator);
    denominator = (rhs.numerator * denominator);
    *this = Fraction(numerator, denominator);
    return *this;
}

Fraction& Fraction::operator/(Fraction rhs){
    *this = *this/=rhs;
    return *this;
}

bool Fraction::operator==(Fraction rhs){
    return (numerator == rhs.numerator && denominator == rhs.denominator);
}

bool Fraction::operator!=(Fraction rhs){
    return !(*this==rhs);
}

bool Fraction::operator<(Fraction rhs){
    return ((numerator/denominator) < (rhs.numerator/rhs.denominator));
}

bool Fraction::operator<=(Fraction rhs){
    return (*this==rhs || *this < rhs);
}

bool Fraction::operator > (Fraction rhs){
    return !(*this <= rhs);
}

bool Fraction::operator>=(Fraction rhs){
    return !(*this < rhs);
}
