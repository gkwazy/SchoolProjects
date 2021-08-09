//
//  WordsHelper.cpp
//  stringAnalyzer
//
//  Created by Garret Wasden on 8/31/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <string>
#include "LetterHelper.hpp"

using namespace std;

//- Returns the number of words in the string.
int NumWords(string s){
    int stringCounter = 1;
    for (int i = 0; i < s.size(); i++){
        if ( s[i] == ' '){
            stringCounter++;
        }
    }
    return stringCounter;
}

//- Returns the number of sentences in the string. This function can make use of the IsPunctuation helper.
int NumSentences(string s){
    int sentenceCounter = 0;
    for (int i = 0; i < s.size(); i++){
       if ( IsTerminator(s[i])){
           sentenceCounter++;
       }
    }
    return sentenceCounter;
}

//- Returns the number of vowels in the string. This function can make use of the IsVowel helper.
int NumVowels(string s){
    int vowelCounter = 0;
    for (int i = 0; i < s.size(); i++){
        if ( IsVowel(s[i])){
            vowelCounter++;
        }
    }
    return vowelCounter;
}

//- Returns the number of consonants in the string. This function can make use of the IsConsonant helper.
int NumConsonants(string s) {
    int consonantCounter = 0;
    for (int i = 0; i < s.size(); i++){
        if ( IsConsonant(s[i])){
            consonantCounter++;
        }
    }
    return consonantCounter;
}

//- Returns the average length of all words in the string. This function can make use of the IsVowel , IsConsonant , and NumWords helpers, as discussed in the Analysis section above.
double AverageWordLength(string s){
    int vowels = NumVowels(s), consonants = NumConsonants(s), words = NumWords(s);
    double averageWordSize = (vowels + consonants) / words;
    return averageWordSize;
}

// - Returns the average number of vowels per word in the string. This function can make use of the IsVowel and NumWords helpers, as discussed in the Analysis section above.
double AverageVowelsPerWord(string s){
    int vowels = NumVowels(s), words = NumWords(s);
    double avgVowelsPerWord = (double)vowels/(double)words;
    return avgVowelsPerWord;
}

string LowerCase(string s){
    for ( int i = 0; i < s.size(); i++){
        s[i] = tolower(s[i]);
    }
    return s;
}
