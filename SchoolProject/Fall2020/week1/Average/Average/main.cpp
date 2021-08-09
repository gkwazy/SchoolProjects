//
//  main.cpp
//  Average
//
//  Created by Garret Wasden on 8/25/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    float first;
    float second;
    float third;
    float fourth;
    float fifth;
    
    std::cout << "Enter the 5 assigments. After each assignment press Enter or the Space Bar: \n";
    std::cin >> first >> second >> third >> fourth >> fifth;
    std::cout << "The average for the scores you have entered ( "
    <<first
    <<", "
    <<second
    <<", "
    <<third
    <<", "
    <<fourth
    <<", "
    <<fifth
    <<") is: \n"
    <<(first + second + third + fourth + fifth)/5
    <<"\n";
    
    
    return 0;
}
