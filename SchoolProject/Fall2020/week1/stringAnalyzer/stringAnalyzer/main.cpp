//
//  main.cpp
//  stringAnalyzer
//
//  Created by Garret Wasden on 8/28/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include <string>
#include "LetterHelper.hpp"
#include "WordsHelper.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    bool programRunning = true;
    while(programRunning){
        int wordsAmount, sentencesAmount,vowelAmount, consonantAmount;
        double readingLevel, avgVowelsPerWord;
        string userString;
//asking for the string from user
        cout << "\nEnter a string containing one or more sentences: (enter \"stop\" to quit program)\n";
        std::getline(std::cin, userString);
        userString = LowerCase(userString);
// checking is exit condution of user typeing stop
        if (userString == "stop"){
            return 1;
        }
// grabbing and storing values from string with functions;
        else{
            wordsAmount = NumWords(userString);
            sentencesAmount = NumSentences(userString);
            vowelAmount = NumVowels(userString);
            consonantAmount = NumConsonants(userString);
            readingLevel = ((double)vowelAmount + (double)consonantAmount) / (double)wordsAmount;
            avgVowelsPerWord = AverageVowelsPerWord(userString);
// printing info for user;
            cout << "\nNumber of words: " << wordsAmount << endl
            <<  "Number of sentences: " << sentencesAmount << endl
            << "Number of vowels: " << vowelAmount << endl
            << "Number of consonants: " << consonantAmount << endl
            << "Reading level (average word length): " << readingLevel << endl
            << "Average vowels per word: " << avgVowelsPerWord << endl;
        }
    }
    return 0;
}
