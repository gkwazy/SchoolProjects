//
//  VectorFunctions.cpp
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

#include "VectorFunctions.hpp"
#include <vector>
#include <string>

using namespace std;
//getting the sum of all the int's in the vector
int vectorsSum(vector<int> usersVector){
    int sum = 0;
    for (int number : usersVector){
        sum += number;
    }
    return sum;
}
//turning a string to a vector
vector<char> stringToVec(string userString){
    vector<char> returnedVector;
    for ( int i = 0; i < userString.size(); i++){
        returnedVector.push_back(userString[i]);
    }
    return returnedVector;
}

//reverse the order of the int's in a vector
vector<int> reverseUserVector(vector<int> originalVector){
    vector<int>reversedVector;
    for ( int i = 0; i < originalVector.size(); i++){
        reversedVector.push_back(originalVector[originalVector.size()-(i+1)]);
        }
    return reversedVector;
}
