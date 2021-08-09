//
//  main.cpp
//  BookAnalyzer
//
//  Created by Garret Wasden on 9/7/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "BookAnalyzer.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
    results bookResults;
    string fileName, wantedWord;
    bookResults.title = "unknown";
    bookResults.author = "unknown";
    vector<string> book;
//    cout << "Please enter the file and word you would like to look up:\n";
//    cin >> fileName >> wantedWord;
    if(argc == 3) {
        fileName = argv[1];
        wantedWord = argv[2];
    }
    book = getBookText(fileName);
        bookResults.wantedWord = wantedWord;
        
    if (book.size() == 0){
        cout << "Sorry no file of the name was found. Closing Program";
        return 1;
    }
    bookResults.totalWords = wordCount(book);
    bookResults.title = getTitle(book);
    bookResults.author = getAuthor(book);
    itemCounter(book, bookResults);
    
   cout<< "Statistics for " << bookResults.title << "\n"
    <<"by " <<bookResults.author << "\n"
    << "Number of words: "<< bookResults.totalWords << "\n"
    << "Number of characters: " << bookResults.totalCharaters<< "\n"
    << "The shortest word is \"" << bookResults.shortestWord<< "\"\n"
    <<"The longest word is \"" << bookResults.longestWord<< "\"\n"
    << "The word " << bookResults.wantedWord <<" appears " << bookResults.wantedWordCount <<" times:\n";
    for(int i = 0; i < bookResults.wantedWordExample.size(); i++){
        printf(" at %.2f %% \"%s\" \n ",bookResults.wantedWordExample[i].percent,bookResults.wantedWordExample[i].words.c_str());
    }
    return 0;
}
