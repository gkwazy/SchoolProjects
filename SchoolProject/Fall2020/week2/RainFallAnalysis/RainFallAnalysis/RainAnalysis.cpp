//
//  RainAnalysis.cpp
//  RainFallAnalysis
//
//  Created by Garret Wasden on 9/3/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include "RainAnalysis.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

string cityName(string file){
    ifstream textFile(file);
    string cityName;
    getline(textFile,cityName);
    return cityName;
    }

vector <Day> inputData(string file){
    vector <Day> days;
    ifstream textFile(file);
    // skipping first line;
    string cityName;
    getline(textFile,cityName);
    for (int i=0; i < 240; i++){
        Day tempDay;
        textFile >> tempDay.month;
        textFile >> tempDay.year;
        textFile >>tempDay.rainFall;
        days.push_back(tempDay);
    }
    return days;
}

void outputData(string fileText){
    ofstream file("rainfall_results.txt");
    file << fileText;
}

string twoDecimalRainString(double rainFall){
    stringstream stream;
    stream << fixed << setprecision(2) <<rainFall;
    string rainFallString = stream.str();
    return rainFallString;
}

double averageRainFall(vector<Day> dates){
    double average = 0;
    for(Day date: dates){
        average += date.rainFall;
    }
    average = average/dates.size();
    return average;
}

double averageMonthRainFall(vector<Day> dates, string month){
    vector<Day> tempDates;
    for(Day date:dates){
        if (date.month == month){
            tempDates.push_back(date);
        }
    }
    return averageRainFall(tempDates);
}

//pushing the first 4 values then compairing the vectors to though four;
vector<double> wettestMonths(vector<Day> dates){
    vector<double>rainNumber;
    for(Day date: dates){
        rainNumber.push_back(date.rainFall);
    }
    sort(rainNumber.begin(), rainNumber.end(), greater<>());
    vector<double> rainFallList = {rainNumber[0], rainNumber[1], rainNumber[2], rainNumber[3]};
    return rainFallList;
}

vector<double> driestMonths(vector<Day> dates){
    vector<double>rainNumber;
    for(Day date: dates){
        rainNumber.push_back(date.rainFall);
    }
    sort(rainNumber.begin(), rainNumber.end());
    vector<double> rainFallList = {rainNumber[0], rainNumber[1], rainNumber[2], rainNumber[3]};
    return rainFallList;
}

bool compareByRain(const Day& dateA, const Day& dateB){
    return dateA.rainFall < dateB.rainFall;
}

vector<Day> medianMonth(vector<Day> dates){
    sort(dates.begin(), dates.end(), compareByRain);
    vector<Day> median;
    if (dates.size() % 2 == 0){
        median.push_back(dates[dates.size()/2]);
        median.push_back(dates[(dates.size()/2)+1]);
    }
    else{
       Day oddDates = {"none",0,0};
       median.push_back(oddDates);
       median.push_back(dates[dates.size()/2]);
    }
    return median;
}


