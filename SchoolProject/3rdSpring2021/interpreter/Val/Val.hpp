//
//  Val.hpp
//  MSD6015
//
//  Created by Garret Wasden on 2/25/21.
//

#ifndef Val_hpp
#define Val_hpp

#include "../catch.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "../pointer.h"

class Expr;
class Env;
class Cont;
class Step;

CLASS(Val) {
    
public:
    virtual PTR(Expr) to_expr() = 0;
    virtual PTR(Val) add_to(PTR(Val) other_val) = 0;
    virtual PTR(Val) mult_to(PTR(Val) other_val) = 0;
    virtual bool equals(PTR(Val) v) = 0;
    virtual bool is_true() = 0;
    virtual PTR(Val) call(PTR(Val) acutal_arg) = 0;
    virtual void call_step(PTR(Val) acutal_arg_val, PTR(Cont) rest) = 0;
};
    
class NumVal : public Val {
public:
    int value;
    PTR(Expr) to_expr();
    NumVal(int value);
    bool equals(PTR(Val) v);
    PTR(Val) add_to(PTR(Val) other_val);
    PTR(Val) mult_to(PTR(Val) other_val);
    bool is_true();
    PTR(Val) call(PTR(Val) acutal_arg);
    void call_step(PTR(Val) acutal_arg_val, PTR(Cont) rest);
};

class BoolVal : public Val {
public:
    bool value;
    PTR(Expr) to_expr();
    bool equals(PTR(Val) v);
    BoolVal(bool value);
    PTR(Val) add_to(PTR(Val) other_val);
    PTR(Val) mult_to(PTR(Val) other_val);
    bool is_true();
    PTR(Val) call(PTR(Val) acutal_arg);
    void call_step(PTR(Val) acutal_arg_val, PTR(Cont) rest);
    
};

class FunVal : public Val{
public:
    std::string formal_arg;
    PTR(Env) env;
    PTR(Expr) body;
    PTR(Expr) to_expr();
    bool equals(PTR(Val) v);
    FunVal(std::string formal_arg, PTR(Expr) body, PTR(Env) env);
    PTR(Val) add_to(PTR(Val) other_val);
    PTR(Val) mult_to(PTR(Val) other_val);
    bool is_true();
    PTR(Val) call(PTR(Val) acutal_arg);
    std::string to_string();
    void call_step(PTR(Val) acutal_arg_val, PTR(Cont) rest);
};


#include <stdio.h>

#endif /* Val_hpp */
