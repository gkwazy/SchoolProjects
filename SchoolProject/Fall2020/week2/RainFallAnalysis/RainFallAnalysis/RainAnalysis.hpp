//
//  RainAnalysis.hpp
//  RainFallAnalysis
//
//  Created by Garret Wasden on 9/3/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#ifndef RainAnalysis_hpp
#define RainAnalysis_hpp

#include <stdio.h>
#include <string>

using namespace std;

struct Day{
    string month;
    int year;
    double rainFall;
};

string cityName(string name);
vector<Day> inputData(string file);
void outputData(string fileText);
string twoDecimalRainString(double rainFall);
double averageRainFall(vector<Day> dates);
double averageMonthRainFall(vector<Day> dates, string month);
vector<double> wettestMonths(vector<Day> dates);
vector<double> driestMonths(vector<Day> dates);
vector<Day> medianMonth(vector<Day> dates);



#endif /* RainAnalysis_hpp */
