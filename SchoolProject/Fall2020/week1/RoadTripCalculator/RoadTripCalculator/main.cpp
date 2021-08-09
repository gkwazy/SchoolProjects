//
//  main.cpp
//  RoadTripCalculator
//
//  Created by Garret Wasden on 8/25/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include <iomanip>

int main(int argc, const char * argv[]) {
    // insert code here...
    float travelMiles, mPG, costOfGallon;
    std::cout << "Welcome the old world before covid where traveling was thing.\n"
              <<"We are going to be planning out the cost to the fun active done back in the day called \"Taking A Road Trip\".\n"
              << "The first Question for our trip is how far is the trip in miles?\n";
    std::cin >> travelMiles;
    std::cout << "\nPerfect, next tell me that is your cars mile per gallon, that is if you have one? If not I would end the program and consider a hike instead. \n";
    std::cin >> mPG;
    std::cout << "Last we will need to get the cost for a gallon of gas, so if you dont mind please enter the dollar amount: \n";
    std::cin >> costOfGallon;
    float gallonsUsed = travelMiles/mPG;
    std::cout  << "So after doing doing the math and burning out 3 cores on my CPU in the process here is the information I got: \nOn this trip you will use "
    << std::setprecision (2) << gallonsUsed
    << " gallons of gas. \nThis trip will cost you about $"
    << std::fixed << std::setprecision(2) << gallonsUsed * costOfGallon
    << "\n";
    return 0;
}
