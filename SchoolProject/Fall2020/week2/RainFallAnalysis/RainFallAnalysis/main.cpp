//
//  main.cpp
//  RainFallAnalysis
//
//  Created by Garret Wasden on 9/3/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "RainAnalysis.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    vector<string> fileVector = {"Atlanta.txt", "Macon.txt"};
    vector<string> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
// main string that will be written to the file after program.
    string fileText = "CS 6010 Rain Analysis";
    
//loops through all the city files and adds to the fileText to write to file.
    for(string file:fileVector){
        vector<Day> dates = inputData(file);
        fileText += "\n\nRainfall data for " + cityName(file) +  ":\n";
        fileText  += "The overall average rainfall amount is " +                         twoDecimalRainString(averageRainFall(dates)) + " inches.\n";
        
        for(string month:months){
            fileText += "The average rainfall amount for " + month + " is " + twoDecimalRainString(averageMonthRainFall(dates, month)) + " inches.\n";
        }
        
        fileText += "The rain amounts (in inches) of the four wettest months are:";
        for(double rainNumber: wettestMonths(dates)){
            fileText += " " + twoDecimalRainString(rainNumber);
        }
        fileText += "\nThe rain amounts (in inches) of the four driest months are:";
        for(double rainNumber: driestMonths(dates)){
            fileText += " " + twoDecimalRainString(rainNumber);
        }
        vector<Day> medians = medianMonth(dates);
        fileText += "\nThe median months are:\n";
        if (medians[0].year == 0){
            fileText += medians[1].month + " " + to_string(medians[1].year) + " " +twoDecimalRainString(medians[1].rainFall);
        }
        else{
            fileText += medians[0].month + " " + to_string(medians[0].year) + " " +twoDecimalRainString(medians[1].rainFall) + " and " + medians[1].month + " " + to_string(medians[1].year) + " " +twoDecimalRainString(medians[1].rainFall);
        }
    }
    outputData(fileText);
    return 0;
}
