//
//  BookAnalyzer.cpp
//  BookAnalyzer
//
//  Created by Garret Wasden on 9/7/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include "BookAnalyzer.hpp"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> getBookText(string file){
    vector<string> wordVector;
    ifstream textFile(file);
    string word;
        
    while(textFile >> word){
        for (int i = 0; i < word.size(); i++){
            word[i] = tolower(word[i]);
        }
        wordVector.push_back(word);
    }
    return wordVector;
}

string getTitle(vector<string> book){
    string title = "";
    for(int i = 0; i < book.size();i++){
        if (book[i] == "title:"){
            int titleAddress = i;
            while (book[i] != "author:"){
                if (i > titleAddress + 100){
                    return "unknown";
                }else{
                    string capitiziedWord = book[i];
                    capitiziedWord[0] = toupper(capitiziedWord[0]);
                    title += capitiziedWord + " ";
                    i++;
                }
            }
            return title;
        }
    }
    return "unknown";
}

string getAuthor(vector<string> book){
    string author = "";
    for(int i = 56; i < book.size();i++){
        if (book[i] == "author:"){
            int authorAddress = i;
            while (book[i+1] != "date:"){
                if (i > authorAddress + 100){
                    return "unknown";
                }else{
                    string capitiziedWord = book[i];
                    capitiziedWord[0] = toupper(capitiziedWord[0]);
                    author += capitiziedWord + " ";
                    i++;
                }
            }
            return author;
        }
    }
    return "unknown";
}

int wordCount(vector<string> book){
    int count = (int)book.size()-1;
    return count;
}
int charaterCounter(string word){
    int wordLength = (int) word.size();
    return wordLength;
}

void itemCounter(vector<string> book, results &bookResults){
    bookResults.longestWord = book[0];
    bookResults.shortestWord = book[0];
    wordExample wantedWordExample;
    
    for(int i = 0; i < book.size(); i++){
        int currentCharaterPosition = bookResults.totalCharaters;
        bookResults.totalCharaters += charaterCounter(book[i]);
        if (book[i].size() > bookResults.longestWord.size()){
            bookResults.longestWord = book[i];
        }
        if (book[i].size() < bookResults.shortestWord.size()){
            bookResults.shortestWord = book[i];
        }
        if (book[i] == bookResults.wantedWord){
            string testing = book[i];
            string exampleString;
//checking if wanted is at the very beginning or end
            if (i==0){
                exampleString = book[i] + " " + book[i+1];
            }else if ( i == ((int)book.size()-2)){
                exampleString = book[i-1] + " " + book[i];
            }else{
                exampleString = book[i-1] + " " + book[i] + " " + book[i+1];
            }
            wantedWordExample.percent= 0;
            wantedWordExample.charterPosition =currentCharaterPosition;
            wantedWordExample.words = exampleString;
            bookResults.wantedWordExample.push_back(wantedWordExample);
        }
    }
    for (int i = 0 ; i < bookResults.wantedWordExample.size(); i++){
        int charPosition = 1 + bookResults.wantedWordExample[i].charterPosition;
        int totalChar = bookResults.totalCharaters;
        double percent = 100*((double)charPosition/(double)totalChar);
        bookResults.wantedWordExample[i].percent = percent;
    }
    bookResults.wantedWordCount = (int)bookResults.wantedWordExample.size();
    
}
