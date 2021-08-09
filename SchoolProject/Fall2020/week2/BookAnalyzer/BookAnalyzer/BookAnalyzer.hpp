//
//  BookAnalyzer.hpp
//  BookAnalyzer
//
//  Created by Garret Wasden on 9/7/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#ifndef BookAnalyzer_hpp
#define BookAnalyzer_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;


struct wordExample {
    double percent;
    int charterPosition;
    string words;
};

struct results {
    string title;
    string author;
    int totalCharaters;
    int totalWords;
    string shortestWord;
    string longestWord;
    string wantedWord;
    int wantedWordCount;
    vector<wordExample> wantedWordExample;
};

void getBookStats(results &bookResults, vector<string> book);
vector<string> getBookText(string file);
int wordCount(vector<string> book);
string getTitle(vector<string> book);
string getAuthor(vector<string> book);
void itemCounter(vector<string> book, results &bookResults);


#endif /* BookAnalyzer_hpp */
