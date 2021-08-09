//
//  main.cpp
//  Functions
//
//  Created by Garret Wasden on 8/28/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//
//**Question 1: this code look to me that it is making a custom variable type (time). then the code is calling
//    the method localtime to get the number of seconds from epoch. std::time is also a method call to make
//    the variable.

//**Question 2: you would not want to get the std:cin from your function because you are only able to return one
//item. so you would not be able to save it and do the math you are wanting to do in the function.

//** Question 3: it would be hard to trun the speed/velocity task into a fuction because you have two different values you are trying to get but your return can only have one value.

//** Question 4: you could have it return a array so that you can pars out the data from it.



#include <iostream>
#include <string>
#include <math.h>

using namespace std;

// function to find out the length
float findLengthOfHypotenuse(float sideA, float sideB){
    float sideCSquared = pow(sideA,2) + pow(sideB,2);
    sideCSquared = sqrt(sideCSquared);
    return sideCSquared;
}

bool isEven(int userNumber){
   
    if (userNumber%2 == 0){
        return true;
    }
    else {
        return false;
    }
}

// This function check if the product of 2 with any number below the given number equal the given number
// then it will do the same with all the number from 2 to the given number. 
bool isPrime(int userNumber){
    bool primeBool = true;
    for (int i = 2; i < userNumber; i++){
        for (int j = 1; j < userNumber; j++){
            if ((j*i == userNumber)){
                primeBool = false;
                return primeBool;
            }
        }
    }
    return primeBool;
}


int main(int argc, const char * argv[]) {
    float sideA, sideB, hypotenuse;
    double speedOfUser, angleOfUser, xUserVelocity, yUserVelocity ;
    int usersEvenNumber;
    bool evenOddBool, primeBool;
    string isOrIsNotPrime = "", isOrIsNotEven = "";

    
// ** This is section "a" for the lab, asking the use for two sides then running the
//    fuction to get the lenght of the hypotenuse.
    cout << "Please enter the right sides of your triangle:\n";
    cin >> sideA >> sideB;
//see if the numbers are positive.
    if ( sideA < 0 && sideB < 0){
        cout<< "Sorry the lenghts need to be positive\n";
        return 1;
    }
//** part 2: this is calling my function to do the math for me to find out the length of the hypotenuse.
    hypotenuse = findLengthOfHypotenuse(sideA,sideB);
    cout <<"The hypotenuse of the right triangle is " << hypotenuse << endl;
    
//**This is section "b" of the lab
//    asking use for their speed and angle.
    cout << "What speeed are you going?\n";
    cin >> speedOfUser;
    cout << "What angle are you moving at?\n";
    cin >> angleOfUser;
//    running the math on the speed and angle to get the velocity for x and y
    xUserVelocity = speedOfUser * cos(angleOfUser);
    yUserVelocity = speedOfUser * sin(angleOfUser);
    
    cout << " Your x velocity is: " << xUserVelocity
    << " and your y velocity is " << yUserVelocity << endl;
    
//** part 2 isEven
    cout << "Pick a whole number:\n";
    cin >> usersEvenNumber;
    evenOddBool = isEven(usersEvenNumber);
    primeBool = isPrime(usersEvenNumber);
    
    if (!evenOddBool){
        isOrIsNotEven = "not ";
    }
    if(!primeBool){
        isOrIsNotPrime = "not ";
    }
    
    cout << "Your number is "<< isOrIsNotEven << "Even and is "<< isOrIsNotPrime<< "Prime.\n";
    
    
    
    
    

    
    return 0;
}
