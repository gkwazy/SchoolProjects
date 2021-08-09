//
//  cmdline.hpp
//  msdscript
//
//  Created by Garret Wasden on 1/19/21.
//
 
#ifndef cmdline_hpp
#define cmdline_hpp
 
#include <stdio.h>
#include<string>

 
void use_arguments(int, char **);
std::string runCommand(std::string command, std::string input);
 
#endif /* cmdline_hpp */
