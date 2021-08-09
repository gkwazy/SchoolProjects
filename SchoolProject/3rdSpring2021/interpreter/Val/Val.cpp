//
//  Val.cpp
//  MSD6015
//
//  Created by Garret Wasden on 2/25/21.
//


#include <stdexcept>
#include <iostream>
#include "Val.hpp"
#include "../Expr/Expr.hpp"
#include "../Env/Env.hpp"
#include "../Cont/Cont.hpp"
#include "../Step/Step.hpp"
#include <string>
#include "../pointer.h"
 

//NumVal functions
NumVal::NumVal(int value){
    this->value = value;
}

PTR(Val) NumVal::add_to(PTR(Val) other_val) {
  PTR(NumVal) other_num = CAST(NumVal)(other_val);
  if (other_num == NULL) throw std::runtime_error("add of non-number");
//    if ((value > 0) && (other_num->value > INT_MAX - value)){
//        throw std::runtime_error("Int OverFlow when adding");
//    }
//    if ((value < 0) && (other_num->value < INT_MIN - value)){
//        throw std::runtime_error("Int UnderFlow when adding");
//    }
  return NEW(NumVal)((unsigned)value + (unsigned)other_num->value);
}

PTR(Val) NumVal::mult_to(PTR(Val) other_val) {
  PTR(NumVal) other_num = CAST(NumVal)(other_val);
  if (other_num == NULL) throw std::runtime_error("mult of non-number");
//    if(value > (INT_MAX/other_num->value)){
//        throw std::runtime_error("Int OverFlow when Multiplying");
//    }
  return  NEW(NumVal)((unsigned)value * (unsigned)other_num->value);
}

bool NumVal::equals(PTR(Val) v){
    PTR(NumVal) v_num = CAST(NumVal)(v);
    if (v_num == NULL){
        return false;
    }else{
        return this->value == v_num->value;
    }
};

PTR(Expr) NumVal::to_expr(){
    PTR(NumExpr) expr = NEW(NumExpr)(this->value);
    return expr;
}

bool NumVal::is_true() {
    throw std::runtime_error("istrue of number");
}

PTR(Val) NumVal::call(PTR(Val) acutal_arg){
    throw std::runtime_error("call on NumVal");
};


void NumVal::call_step(PTR(Val) acutal_arg_val, PTR(Cont) rest){
    throw std::runtime_error("call_step on NumVal");
}

//BoolVal constructor;
BoolVal::BoolVal(bool value){
    this->value = value;
}

bool BoolVal::equals(PTR(Val) v){
    PTR(BoolVal) v_bool = CAST(BoolVal)(v);
    if (v_bool == NULL){
        return false;
    }else{
        return this->value == v_bool->value;
    }
};

//adding Vals together
PTR(Val) BoolVal::add_to(PTR(Val) other_val) {
  throw std::runtime_error("add of non-number");
}

PTR(Val) BoolVal::mult_to(PTR(Val) other_val) {
    throw std::runtime_error("Mult of non-number");
}

PTR(Expr) BoolVal::to_expr(){
    PTR(BoolExpr) expr = NEW(BoolExpr)(this->value);
    return expr;
}

bool BoolVal::is_true() {
    return this->value;
}

PTR(Val) BoolVal::call(PTR(Val) acutal_arg){
    throw std::runtime_error("call on BoolVal");
};

void BoolVal::call_step(PTR(Val) acutal_arg_val, PTR(Cont) rest){
    throw std::runtime_error("call_step on BoolVal");
}


//FunVals
FunVal::FunVal(std::string formal_arg, PTR(Expr) body, PTR(Env) env){
    this->formal_arg = formal_arg;
    this->body = body;
    this->env = env;
};

PTR(Expr) FunVal::to_expr(){
    PTR(FunExpr) fun = NEW(FunExpr)(this->formal_arg, this->body);
    return fun;
};

PTR(Val) FunVal::add_to(PTR(Val) other_val){
    throw std::runtime_error("add of Functions");
};

PTR(Val) FunVal::mult_to(PTR(Val) other_val){
    throw std::runtime_error("Mult of Functions");
};

bool FunVal::equals(PTR(Val) v){
    PTR(FunVal) v_Fun = CAST(FunVal)(v);
    if (v_Fun == NULL){
        return false;
    }else{
        return this->formal_arg == v_Fun->formal_arg && this->body->equals(v_Fun->body);
    }
};
bool FunVal::is_true(){
    throw std::runtime_error("is_true of Functions");
};

PTR(Val) FunVal::call(PTR(Val) actual_arg){
    PTR(Val) val = this->body->interp(NEW(ExtendedEnv)(this->formal_arg, actual_arg, this->env));

    return val;
};

std::string FunVal::to_string(){
    return "[function]";
};

void FunVal::call_step(PTR(Val) acutal_arg_val, PTR(Cont) rest){
    Step::mode = Step::interp_mode;
    Step::expr = body;
    Step::env = NEW(ExtendedEnv)(formal_arg, acutal_arg_val, env);
    Step::cont = rest;
}

