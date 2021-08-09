//
//  main.cpp
//  VectorPractice
//
//  Created by Garret Wasden on 8/31/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//
//In a project named VectorPractice, do the following:
//
//Write a function sum that takes a vector of ints as a parameter and returns the sum of all the values in the vector. Add code in main to test this function.
//
//Write a function stringToVec that takes a string as a parameter and returns a vector of chars that contains the same data. Note that even though they contain the data, these data types are different! For example, you can't call the substr method on the vector of chars. Test your function in main.
//
//Write a function reverse that takes a vector of ints and returns a vector with the same elements in reverse order. Test your function in main.

#include <iostream>
#include <vector>
#include"VectorFunctions.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    vector<int> testingIntVector;
    vector<int> testingReversedVector;
    
    for (int i = 1; i <= 30; i ++){
        testingIntVector.push_back(i);
        
    }
     cout <<"\n";
    
    int testingSum = vectorsSum(testingIntVector);
    cout << testingSum  << ", ";
    cout <<"\n";
    
    vector<char> testingCharVector = stringToVec("hope you have a nice day");
    cout <<"\n";
    
    for ( char charter: testingCharVector){
        cout << charter;
    }
    cout <<"\n";
    
    testingReversedVector = reverseUserVector(testingIntVector);
    
    for (int number: testingReversedVector){
        cout << number << ", ";
    }
    cout <<"\n";
    
    return 0;
}
