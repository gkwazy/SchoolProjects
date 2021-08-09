//
//  WordsHelper.hpp
//  stringAnalyzer
//
//  Created by Garret Wasden on 8/31/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#ifndef WordsHelper_hpp
#define WordsHelper_hpp

#include <stdio.h>
#include<string>


using namespace std;

int NumWords(string s);

int NumSentences(string s);

int NumVowels(string s);

int NumConsonants(string s);

double AverageWordLength(string s);

double AverageVowelsPerWord(string s);

string LowerCase(string s);

#endif /* WordsHelper_hpp */
