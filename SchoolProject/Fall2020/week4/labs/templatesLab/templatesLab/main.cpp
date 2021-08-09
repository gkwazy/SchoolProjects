//
//  main.cpp
//  templatesLab
//
//  Created by Garret Wasden on 9/20/20.
//

#include <iostream>
#include <string>
#include <vector>
#include "templatesLab.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    Triple<string> typestring {"1","2","3"};
    Triple<int> typeint {1,2,3};
    Triple<vector<int>> typevector =
    {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    
    cout << addTemplate(typestring)<< endl;
    cout << addTemplate(typeint) << endl;
//    cout << addTemplate(typevector) << endl; endl;
// when calling this function because of the way that the method is written it cant get into the vectors the way it needs to so it trying to add vector + vector and for that i woul dether need to over load the vector or i would need to rewrite the method to check for vectors. 
    return 0;
}
