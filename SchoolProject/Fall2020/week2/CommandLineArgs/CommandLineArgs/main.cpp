//
//  main.cpp
//  CommandLineArgs
//
//  Created by Garret Wasden on 9/7/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include <iostream>
// this first element in argv is /main or the program.
int main(int argc, const char * argv[]) {
    for(int i = 1; i<argc; i++){
    std::string word = argv[i];
        std::cout << word << std::endl;
    }
    return 0;
}
