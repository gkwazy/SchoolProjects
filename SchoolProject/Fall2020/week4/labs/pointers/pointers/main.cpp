//
//  main.cpp
//  pointers
//
//  Created by Garret Wasden on 9/15/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>

double * newDouble(double * originalDouble, double size){
    double * secondDouble = new double[size];
    for (int i = 0; i < size; i++){
        secondDouble[i] = originalDouble[i];
    }
    return secondDouble;
}


int main(int argc, const char * argv[]) {
    
    return 0;
}
