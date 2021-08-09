//
//  NumberAndTextRepresentation.cpp
//  NumberAndTextRepresent
//
//  Created by Garret Wasden on 9/9/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include "NumberAndTextRepresentation.hpp"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int stringToInt(string value, int base){
    int sum = 0;
    int length = (int)value.size();
    reverse(value.begin(),value.end());
    for (int i = 0; i < length; i++){
        int temp = 0;
        if (((int)value[i] > 47) && ((int)value[i] < 58)){
            temp = +value[i]-48;
        }else{
           temp = (int)(tolower(value[i]))-87;
        }
        
        sum+= pow(base,i)*temp;
    }
    return 0; 
}

string Caeser (string word, int number){
    for (int i = 0; i < word.size(); i++){
        if ( word[i] >= 65 && word[i] <= 90){
            upperConverter(word[i], number);
        }else if (word[i] >= 97 && word[i] <= 122){
            lowerConverter(word[i], number);
        }
        else{
            continue;
        }
    }
    return word;
}

void lowerConverter(char &charater, int number){
    charater = ((int)charater % 97) + (number % 26);
    
//    cout << " 1: "<<(number % 26);
    charater = (charater + 26) % 26;
//     cout <<" 2: "<< (int)charater;
    charater = charater + 97;
//    cout << " 3: "<<(int)charater;
}

void upperConverter(char &charater, int number){
    charater = ((int)charater % 65 ) + (number % 26);
//     cout << " 1: "<< (int)charater;
    charater = (charater + 26) % 26;
//    cout <<" 2: "<< (int)charater;
    charater = charater + 65;
//    cout << " 3: "<<(int)charater;
}


