//
//  WordCounter.cpp
//  mapAndSet
//
//  Created by Garret Wasden on 9/23/20.
//

#include "WordCounter.hpp"
#include <vector>
#include <string>
#include <set>
#include <map>
#include <fstream>

using namespace std;


vector<string> getText(string book){
    vector<string> text;
    ifstream booksText(book);
    string word;
    while(booksText >> word){
        for (char &c : word){
            c = tolower(c);
        }
        text.push_back(word);
    }
    
    return text;
}
