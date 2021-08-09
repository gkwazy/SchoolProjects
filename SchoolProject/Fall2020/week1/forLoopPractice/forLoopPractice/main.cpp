//
//  main.cpp
//  forLoopPractice
//
//  Created by Garret Wasden on 8/26/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.

#include <iostream>

// I did not have to rewrite this for multiple parts so I made my loop a function
//The arguments for the function are start #, end # and incremente count.
void myForLoop(int start, int end, int incremente){
    for (int i = start; i <= end; i += incremente){
           std::cout << i
           << " ";
       }
}

int main(int argc, const char * argv[]) {
// all of my variables I will need
    int loopNumber = 1;
    int start, end, addingTotal = 0, addingNext = 0, addingTemp;
    bool nextNumber = true;
//Print the numbers from 1 to 10. Do this once using a for loop, and once using a while loop. Add a comment indicating which type of loop was more appropriate.
//** I feel that a for loop is the better option because you can more easily control the loop and it is harder to make a mistake that could end up in an infinite loop.
    
//   my for loop exsample:
    myForLoop(1,10,1);
    std::cout << "end of for loop \n";
    
// here is my while loop
    while(loopNumber < 11){
        std::cout << loopNumber
        << " ";
        loopNumber++;
    }
    std::cout << "end of while loop \n";
    
//Prompt the user to enter the two numbers. Then print all the numbers from the first to the second. For example, if the user entered 25 and 40, you should print 25, 26, 27, ... 39, 40. What happens/should happen if the numbers come in reverse order?
//** if the numbers came in reverse order the loop never starts, I added a check so that it will start with the lower number and count up to the higher one
//This is so the user can choose the first and last
    std::cout << "Please choose a whole number to start with and to end with:\n";
    std::cin >> start >> end;
    if (start > end){
        int temp = start;
        start = end;
        end = temp;
    }
    myForLoop(start, end, 1);
    std::cout << "end of for loop \n";
    
//Print all the odd numbers between 1 and 20. Come up with two solutions: one that uses a loop and an if statement, and one that doesn't require an if statement. Comment on which you think is better.
//** I feel that the loop without the if was easier to write and use. because I already had a function I could just use that same fuction for this operation as well.
    
//Printing odd number with a if statment
    for (int i = 1; i<=20; i++){
        if(i % 2 != 0){
            std::cout << i;
        };
    }
    std::cout << " for loop with if statment printing odd numbers. \n";
// Printing odd numbers 1-20 I will use my fuction but set the incrament to 2 starting with 1
    myForLoop(1, 20, 2);
    
//Ask a user to enter numbers to add up. Keep reading and adding numbers until the user enters a number that is less than 0, then print the sum. For example, if the user entered 1 2 3 -1, you should print 6. This one is a little tricky!
    
    while(nextNumber){
        std::cout << "Enter a Number to add to the total or enter a negative number to quit. So far the total is:"
        << addingTotal << std::endl;
        std::cin >> addingNext;
        if (addingNext <= 0){
            nextNumber = false;
        }
        else {
            addingTotal += addingNext;
        }
    }
    std::cout << "The Grand total is:"
    << addingTotal << std::endl;
    
    
//Print a multiplication table for the numbers 1 to 5.
    
    for ( int i = 1; i <= 5; i++){
        myForLoop(i,(i*5),i);
        std::cout << "\n";
    }
    
    return 0;
}

