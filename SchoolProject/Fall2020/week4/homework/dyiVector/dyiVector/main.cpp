//
//  main.cpp
//  dyiVector
//
//  Created by Garret Wasden on 9/15/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
#include <numeric>
#include <string>
#include <functional>
#include "dyiVector.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    myVector<int> vector1(1);
    myVector<char> vectorChar(1);
    myVector<int> vectorBig(1);
    myVector<int> vectorSmall(1);
    myVector<int> vectorAlpha(1);
    
    
    assert(vector1.getCapacity() == 1);
    assert (vector1.getSize() == 0);
    vector1.pushBack(1);
    vector1.pushBack(2);
    vector1.pushBack(3);
    vector1.pushBack(4);
    vector1.pushBack(5);
    vector1.pushBack(6);
    assert(vector1.getCapacity() == 8);
    assert (vector1.getSize() == 6);
    vector1.popBack();
    assert(vector1.getCapacity() == 8);
    assert (vector1.getSize() == 5);
    assert(vector1[4] == 5);
    vector1[4]=20;
    assert(vector1[4] == 20);
    assert(vector1.get(1) == 2);
    vector1.freeVector();
    
    
    
// building a new vector with char, placing 6
// chars in it then removing one to see if passes.
    
   
    
    assert(vectorChar.getCapacity() == 1);
    assert (vectorChar.getSize() == 0);
    vectorChar.pushBack('a');
    vectorChar.pushBack('b');
    vectorChar.pushBack('c');
    vectorChar.pushBack('d');
    vectorChar.pushBack('e');
    vectorChar.pushBack('f');
    assert(vectorChar.getCapacity() == 8);
    assert (vectorChar.getSize() == 6);
    vectorChar.popBack();
    assert(vectorChar.getCapacity() == 8);
    assert (vectorChar.getSize() == 5);
    assert(vectorChar[4] == 'e');
    vectorChar[4]='g';
    assert(vectorChar[4] == 'g');
    assert(vectorChar.get(1) == 'b');
    vectorChar.freeVector();
    
// testing for operator
   
    vectorBig.pushBack(11);
    vectorBig.pushBack(12);
    vectorBig.pushBack(13);
    vectorBig.pushBack(14);
    vectorBig.pushBack(15);
    vectorBig.pushBack(16);
    
    vectorSmall.pushBack(11);
    vectorSmall.pushBack(12);
    vectorSmall.pushBack(3);
    vectorSmall.pushBack(14);
    vectorSmall.pushBack(15);
    vectorSmall.pushBack(16);
    
    vectorAlpha.pushBack('a');
    vectorAlpha.pushBack('b');
    vectorAlpha.pushBack('c');
    vectorAlpha.pushBack('d');
    vectorAlpha.pushBack('e');
    vectorAlpha.pushBack('f');
    
    std::sort(vectorSmall.begin(), vectorSmall.end());
    
    for (int i: vectorSmall){
        cout<< i << endl;
    }
    
    cout << *std::min_element(vectorSmall.begin(), vectorSmall.end()) << endl;
    
    int sum = std::accumulate(vectorSmall.begin(), vectorSmall.end(),0);
    cout << sum << endl;
    
    long count = std::count_if(vectorSmall.begin(), vectorSmall.end(),[](int i){return i % 2 !=0;});
    cout << count << endl;
    
//std:remove(vectorSmall.begin(), vectorSmall.end(), [](int i){return i%2==0;});
    
    
    
    assert(vectorBig == vectorBig);
    assert(vectorBig != vectorSmall);
    assert(vectorBig > vectorSmall);
    assert(vectorSmall < vectorBig);
    assert(vectorBig >= vectorSmall);
    assert(vectorBig >= vectorBig);
    assert(vectorBig <= vectorBig);
    assert(vectorSmall <= vectorBig);
    assert(vectorBig != vectorAlpha);
    assert(vectorBig <= vectorAlpha);
    assert(vectorBig < vectorAlpha);
    
    
    vectorSmall = vectorAlpha;
    assert(vectorSmall == vectorAlpha);
    
    
    cout << "winner" << endl;
    
    
    
    
    
    
    
    
    
    return 0;
}
