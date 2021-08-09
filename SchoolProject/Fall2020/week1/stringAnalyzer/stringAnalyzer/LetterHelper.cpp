//
//  LetterHelper.cpp
//  stringAnalyzer
//
//  Created by Garret Wasden on 8/31/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

//- Returns whether or not the character is ., ?, or !.
bool IsTerminator(char c){
    if ( c == '.' || c== '?' || c=='!'){
        return true;
    }
    else{
        return false;
    }
}

//- Returns whether or not the character is ., ?, !, or ,.
bool IsPunctuation(char c){
    if ( IsTerminator(c)){
        return true;
    }
    else if ( c==','){
        return true;
    }
    else{
        return false;
    }
}

//- Returns whether or not the character is a vowel. For our purposes, always treat the character 'y' (and its uppercase version) as a vowel.
bool IsVowel(char c){
    if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='y' ){
        return true;
    }
    else{
        return false;
    }
}

//- Returns whether or not the character is a consonant. DO NOT write code that checks if the character is equal to every consonant. In our simple sentences, there are four classifications of characters: spaces, punctuation, vowels, and consonants. If a character is not one of the first three, then it must be a consonant. Use the previous two functions as helpers to determine this. This function can be completed in one simple line of code.
bool IsConsonant(char c){
    if (!IsVowel(c) && !IsPunctuation(c) && c!=' '){
        return true;
    }
    else {
        return false;
    }
}
