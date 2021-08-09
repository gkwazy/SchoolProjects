//
//  main.cpp
//  ifStatementPractice
//
//  Created by Garret Wasden on 8/26/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
//  first asking for the users age
    std::cout << "What is your age?\n";
    int usersAge;
    std::cin >> usersAge;

    std::cout <<"\nBased on your age:\n";
// Next this is a check to see if they can vote
    if (usersAge>=18){
        std::cout << "You are old enough to vote, you better register!\n";
    }
    else{
        std::cout << "Sorry, you are not old enough to vote\n";
    }
//This is checking if they are able to run for senate
    if (usersAge >= 30){
        std::cout << "You are old enough to run for senate, stressful but a rewarding job.\n";
    }
    else{
        std::cout << "Sorry, you are not old enough to run for senate\n";
    }
//This is a list of if that will see what generation they are. It starts out with the oldest possibility and works down from there.
    if (usersAge > 80){
        std::cout <<"Well look at that, your part of the Greatest Generation.\n";
    }
    else if (usersAge <=80 && usersAge > 60){
            std::cout << "A Baby Boomer I see, well the Beatles were a great band.\n";
    }
    else if (usersAge <=60 && usersAge > 40){
        std::cout << "Generdation X, So how was the 80's?\n";
    }
    else if (usersAge <= 40 && usersAge > 20){
        std::cout << "The Millennial or Gen Y, How was using dial up as a kid?\n";
    }
    else {
        std:: cout << "iKid, well we all have to start somewhere.\n";
    }
    
// This is part 2 of the lab I will declare my var here for it asking like it is a new main method
    char weekday;
    char holiday;
    char children;
// Getting information from user about the day and if childeren
    std::cout << "\n Next we will do part 2\n";
    std::cout <<"Y/N, is today a weekday?\n";
    std::cin >> weekday;
    weekday = tolower(weekday);
    std::cout <<"Y/N, is today a holiday?\n";
    std::cin >> holiday;
    holiday = tolower(holiday);
    std::cout <<"Y/N, do you have young childern?\n";
    std::cin >> children;
    children = tolower(children);
//if the user has childern then they will not be able to sleep in
    if (children == 'y' ) {
        std::cout << "Sorry, With young childern you will never be able to sleep in.\n";
    }
    else if (holiday == 'y'){
        std::cout << "Huzzah! you get to sleep in. \n";
    }
    else if (weekday == 'n'){
        std::cout << "Huzzah! you get to sleep in. \n";
            }
    else{
        std::cout << "Sorry, looks like it might be a work day and you need to get up early.\n";
    }
    
    return 0;
}
