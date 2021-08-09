//
//  main.cpp
//  NumberAndTextRepresent
//
//  Created by Garret Wasden on 9/9/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include "NumberAndTextRepresentation.hpp"
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    string commands = "";
    int total = argc;
    string numberString = argv[total-1];
    int number = stoi(numberString);

    for (int i = 1; i < argc-1; i++){
        commands = commands + " " + (argv[i]);

    }
//
//
//
   cout << Caeser (commands, number) << endl;
//   cout << Caeser ("Hello World!", -27) << endl;
//    cout << Caeser ("Hello World!", -1) << endl;
//    cout << Caeser ("Hello World!", 25) << endl;
    
    return 0;
}
