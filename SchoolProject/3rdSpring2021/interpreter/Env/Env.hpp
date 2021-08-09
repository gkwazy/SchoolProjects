//
//  Env.hpp
//  MSD6015
//
//  Created by Garret Wasden on 3/30/21.
//

#ifndef Env_hpp
#define Env_hpp


#include "../catch.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "../pointer.h"

class Val;

CLASS(Env) {
public:
    virtual PTR(Val) lookup(std::string find_name) = 0;
    static PTR(Env) empty;
    
};

class EmptyEnv : public Env{
public:
    EmptyEnv();
    PTR(Val) lookup(std::string find_name);
};

class ExtendedEnv : public Env {
public:
    std::string name;
    PTR(Val) val;
    PTR(Env) rest;
    ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest);
    PTR(Val) lookup(std::string find_name);
    
};
#endif /* Env_hpp */
