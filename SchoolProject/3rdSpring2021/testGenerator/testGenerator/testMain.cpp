//
//  main.cpp
//  testGenerator
//
//  Created by Garret Wasden on 2/22/21.
//

#include <stdio.h>
#include "testGen.hpp"


int main(int argc, const char **argv) {
    try{
    testGen test;
    test.runTests(argc, argv);
    return 0;
    } catch(std::runtime_error exn) {
            std::cerr << exn.what() << "\n";
            return 1;
    }
}
