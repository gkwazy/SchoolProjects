//
//  main.cpp
//  StructsLab
//
//  Created by Garret Wasden on 9/1/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//
//Define a struct to describe a politician. It should include fields to keep track of their name, party affiliation, and whether they're a state or federal politician. Assume your politicians operate in a 2-party system (they're each either a republican or a democrat).
//
//Write the following functions below, along with a set of tests in main() to verify that they work correctly.
//
//Write a function named democrats that takes a vector of politicians and returns a vector with only the politicians from the input that are democrats.
//
//Write a function named federalRepublicans that takes a vector of politicians as a parameter and returns a list of the federal republicans from the input.
#include <iostream>
#include <string>
#include <vector>
#include "StuctsLab.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<politician> vectorOfPoliticians;
    politician polyOne {"jim", true, true};
    politician polyTwo { "jan", false, true};
    politician polyThree { "dan", true, false};
    politician polyFour {"pam", false, false};
    politician polyFive {"ham", true, false};
    vectorOfPoliticians.push_back(polyOne);
    vectorOfPoliticians.push_back(polyTwo);
    vectorOfPoliticians.push_back(polyThree);
    vectorOfPoliticians.push_back(polyFour);
    vectorOfPoliticians.push_back(polyFive);
    
    
    
    assert(democrats(vectorOfPoliticians).size() == 2);
    assert(federalRepublicans(vectorOfPoliticians).size() == 2);
      
    cout << "You are a winner!!!!!!" << endl;
    
    
    return 0;
}
