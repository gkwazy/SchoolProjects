//
//  main.cpp
//  VendingMachinePartOne
//
//  Created by Garret Wasden on 8/25/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include <cmath>

int main(int argc, const char * argv[]) {
    int priceOfItem = 0,amountPaid = 0;
    bool unverifiedAmount = true, checkOne, checkTwo;
//This loop is to ask the customer for the price and payment. if the values are not positive then it will reask for the value by looping again. It has two check, for negative values and that the price is less then the cost
    std::cout << "Hello there, just your friendly neighborhood vending machine here ";
    while(unverifiedAmount){
        checkOne = false;
        checkTwo = false;
        std::cout << "please enter the cost of the item you want to purchase as cents:\n";
        std::cin >> priceOfItem;
        std::cout<< "Now enter your payment:\n";
        std::cin >> amountPaid;
        if (priceOfItem <=0 && amountPaid <= 0){
            std::cout << "Ops the price of the item is negative and the amount enterd for paymnet is also negative, please reenter information\n";
        }
        else if (priceOfItem <=0 ){
        std::cout << "Ops the price of the item is negative, please reenter information\n";
        }
        else if (amountPaid <= 0 ){
        std::cout << "Ops the amount enterd for payment is negative, please reenter information\n";
        }
        else{
            checkOne = true;
        }
        if ( priceOfItem <= amountPaid){
            checkTwo = true;
        }
        else{
            std::cout << "It looks like you don't have enough to buy that item.\n";
        }
        if (checkOne == true && checkTwo == true) {
            unverifiedAmount = false;
        }
    }
    std::cout<< "Well hot dog, Im the most trusting venting machine ever! Here is your change:\n"
    <<"The item costs: "
    << priceOfItem
    <<"\nThe user paid: "
    << amountPaid;
    int change = amountPaid - priceOfItem;
    int leftOver = change;
    int quarters = change/25;
    if (quarters > 2){
        quarters = 2;
        leftOver -= 50;
    }
    else{
        leftOver = change%25;
    }
    int dimes = leftOver/10;
    if (dimes > 2){
        dimes = 2;
        leftOver -= 20;
    }else{
        leftOver = leftOver%10;
        
    }
    int nickels = leftOver/5;
    if ( nickels > 2){
        nickels = 2;
        leftOver -= 10;
    }else{
        leftOver = leftOver%5;
    }
    int pennies = leftOver;
    if(pennies > 2){
        std::cout << "\nSorry I dont have enough Change, I can't complete the transaction\n";
      
    }else{
        std::cout << "\nChange = "
        <<change
        <<" cents\n"
        <<"Quarters: "
        << quarters
        <<"\nDimes: "
        <<dimes
        <<"\nNickel: "
        << nickels
        <<"\n Pennies: "
        <<pennies
        <<"\n";
    }
    return 0;
}
