//
//  main.cpp
//  romanNumerals
//
//  Created by Garret Wasden on 8/27/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    int numberToConvert;
    int savedNumberToConvert;
    string romanNumeral="";
    int numeralKey[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string romanKey[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    cout << "Please enter a number: \n";
    cin >> numberToConvert;
    savedNumberToConvert = numberToConvert;
    if(numberToConvert <= 0){
        cout << "Sorry the number needs to be above 0\n";
        return 1;
    }
    else{
    for (int i = 0; i < 13; i++){
        while (numberToConvert - numeralKey[i] >= 0){
            romanNumeral = romanNumeral + romanKey[i];
            numberToConvert = numberToConvert - numeralKey[i];
        }
    }
    cout << savedNumberToConvert << " in roman numerals is " << romanNumeral << endl;
    }
    return 0;
}

