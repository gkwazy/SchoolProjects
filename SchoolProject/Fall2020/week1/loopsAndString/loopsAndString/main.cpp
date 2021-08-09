//
//  main.cpp
//  loopsAndString
//
//  Created by Garret Wasden on 8/27/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
// first half of the project, I worked with Brenda Quiroga, Lili Teeters, Jean Quizro.
int main(int argc, const char * argv[]) {
    string reversed = "";
    string pally;
    cout << "Type a word:\n";
    cin >> pally;
// for loop to take the last char of the string and all it to the reverse string.
    for (int i=0 ; i < pally.size(); i++){
        reversed = reversed + pally[pally.size()-1-i];
    }
    if (reversed == pally){
        cout << pally << " is a palindrome \n";
    }
    else {
        cout << pally << " is NOT a palindrome \n";


    }
    
// second half of the group work. done on my own for practice.
    string date;
    string month;
    string day;
    int monthNumber;
    string year;
    
    cout << "Please enter a date in the format of MM/DD/YYYY\n";
    cin >> date;
    if ( date.size()!= 10){
        cout << "not a valid date, sorry.\n";
    }
    else {
//    01/34/6789
        month = date.substr(0,2);
        day = date.substr(3,2);
        year = date.substr(6,4);
        monthNumber = stoi(month);
//getting month in a word
        if ( monthNumber == 1){
            month = "January";
        }
        if ( monthNumber == 2){
            month = "Febuary";
        }
        if ( monthNumber == 3){
            month = "March";
        }
        if ( monthNumber == 4){
            month = "April";
        }
        if ( monthNumber == 5){
            month = "May";
        }
        if ( monthNumber == 6){
            month = "June";
        }
        if ( monthNumber == 7){
            month = "July";
        }
        if ( monthNumber == 8){
            month = "August";
        }
        if ( monthNumber == 9){
            month = "September";
        }
        if ( monthNumber == 10){
            month = "October";
        }
        if ( monthNumber == 11){
            month = "November";
        }
        if ( monthNumber == 12){
            month = "December";
        }
        cout << month + " " + day +", " + year << endl;

    }
    
// part three, I will just be reusing the variables from part two.
    int dayNumber;
    int yearNumber;

    cout << "Enter a Date:\n";
    cin >> date;

    month = date.substr(0,2);
    day = date.substr(3,2);
    year = date.substr(8,2);
    dayNumber = stoi(day);
    monthNumber = stoi(month);
    yearNumber = stoi(year);

    if (dayNumber * monthNumber == yearNumber){
        cout << date << " is a magic year!\n";
    }
    else {
        cout << date << " is NOT a magic year!\n";
    }

    
    
    return 0;
}
