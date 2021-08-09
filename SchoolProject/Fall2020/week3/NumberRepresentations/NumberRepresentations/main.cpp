//
//  main.cpp
//  NumberRepresentations
//
//  Created by Garret Wasden on 9/9/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include <cstdint>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

bool aproxEquals(double a, double b, double tolerance){
    if(abs(a -b) < tolerance){
        return true;
    }
    return false;
}

void readFile(string file){
    ifstream ins(file);
    char c;
    cout << "ran";
    while(ins >> c){
        cout << c << endl;
    }
}

int main(int argc, const char * argv[]) {
   
//Part one

    int8_t eightIntMin = 0x80; // 1000 0000
    int16_t sixteenIntMin = 0x8000; // 1000 0000 0000 0000
    int64_t sixtyFourIntMin = 0x8000000000000000;// 1000 0000 0000 0000 0000 0000 0000 0000
    int8_t eightIntMax = 0x7F; // 0111 1111
    int16_t sixteenIntMax = 0x7FFF;
    int64_t sixtyFourIntMax = 0x7FFFFFFFFFFFFFFF;

    uint8_t eightUintMax = 0xFF;
    uint16_t sixteenUintMax = 0xFFFF;
    uint64_t sixtyFourUintMax = 0xFFFFFFFFFFFFFFFF;
    uint8_t eightUintMin = 0x00;
    uint16_t sixteenUintMin = 0x0000;
    uint64_t sixtyFourUintMin = 0x0000000000000000;


    cout << sizeof(char) << endl;
    cout << sizeof(bool) << endl;
    cout << sizeof(int) << endl;
    cout << sizeof(float) << endl;
    cout << sizeof(double) << endl;

    cout << "Min unsigned 8: " << +eightUintMin<< endl;
    cout << "Min unsigned 16: " << +sixteenUintMin << endl;
    cout << "Min unsigned 64: " << +sixtyFourUintMin << endl;
    cout << "Max unsigned 8: " << +eightUintMax<< endl;
    cout << "Max unsigned 16: " << +sixteenUintMax << endl;
    cout << "Max unsigned 64: " << +sixtyFourUintMax <<"\n" <<endl;

    cout << "Min signed 8: " << +eightIntMin<< endl;
    cout << "Min signed 16: " << +sixteenIntMin<< endl;
    cout << "Min signed 64: " << +sixtyFourIntMin<< endl;
    cout << "Max signed 8: " << +eightIntMax<< endl;
    cout << "Max signed 16: " << +sixteenIntMax<< endl;
    cout << "Max signed 64: " << +sixtyFourIntMax<< endl;
    eightIntMin -= 1;
    eightIntMax += 1;
// If flips them so the min is now the maxs and max is min.
    cout << "Min signed 8 - 1 : " << +eightIntMin<< endl;
    cout << "Max signed 8 + 1 : " << +eightIntMax<< endl;

// part 2
    double a = .1 + .2, given = .1+.2, wanted = .3, tolerance = .01;
    
    bool worked = aproxEquals(given, wanted, tolerance);
    if (worked){
        cout << "yes\n";
    }else{
        cout<<"no\n";
    }


// Part 3
     readFile("text.txt");
    return 0;
}
