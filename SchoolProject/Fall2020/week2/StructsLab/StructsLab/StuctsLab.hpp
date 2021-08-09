//
//  StuctsLab.hpp
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

#ifndef StuctsLab_hpp
#define StuctsLab_hpp

#include <stdio.h>
#include <string>
using namespace std;

struct politician{
    string name;
    bool isRepubican;
    bool isState;
};

vector<politician> democrats(vector<politician> vecotorOfPoliticians);

vector<politician> federalRepublicans(vector<politician> vecotorOfPoliticians);

#endif /* StuctsLab_hpp */
