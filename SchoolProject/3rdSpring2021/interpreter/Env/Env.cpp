//
//  Env.cpp
//  MSD6015
//
//  Created by Garret Wasden on 3/30/21.
//

#include "Env.hpp"
#include "../pointer.h"


PTR(Env) Env::empty = NEW(EmptyEnv)();

EmptyEnv::EmptyEnv(){
}

PTR(Val) EmptyEnv::lookup(std::string find_name){
        throw std::runtime_error("free variable: "+ find_name);
    }

ExtendedEnv::ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) env){
    this->name = name;
    this->val = val;
    this->rest = env;
}

PTR(Val) ExtendedEnv::lookup (std::string find_name){
    if (find_name == name){
        return val;
    }else{
        return rest->lookup(find_name);
    }
}
