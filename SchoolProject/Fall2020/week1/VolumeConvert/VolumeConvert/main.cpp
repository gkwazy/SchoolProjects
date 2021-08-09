//
//  main.cpp
//  VolumeConvert
//
//  Created by Garret Wasden on 8/25/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
// this progect was done with aaron reeves
int main(int argc, const char * argv[]) {
    // insert code here...
    float oz;
    std::cout << "Please enter the amount in ounces: \n";
    std::cin >> oz;
    std::cout <<"Ounces: "
              << oz
              <<"\nCups: "
              << oz*0.125
              <<"\nPints: "
              << oz*0.0625
              <<"\nGallons: "
              << oz*0.0078125
              <<"\nLiters: "
              << oz*0.0295735
              <<"\nCubic Inches: "
              << oz*1.80469
              <<"\n";
        
        return 0;
}
