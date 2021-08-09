//
//  main.cpp
//  mapAndSet
//
//  Created by Garret Wasden on 9/23/20.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "WordCounter.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    string wantedFile = argv[1];
    
    vector<string> text = getText(wantedFile);
    
    set<string> setList;
    map<string, int> mapList;
    
    for (string word: text){
        bool test = setList.insert(word).second;
        if (setList.insert(word).second){
            setList.insert(word);
            mapList.insert({word, 1});
        }
        else{
            mapList[word] ++;
        }
    }
        int totalNumber = (int)(setList.size()+1);
    
    cout << "Total Number of different words: " << totalNumber << endl;
    
    cout << "List of words with count number: " <<
    endl;
    for(auto word: mapList){
        cout << word.first << " " << word.second << endl;
    }
    
    cout << text.size();
    
    return 0;
}
