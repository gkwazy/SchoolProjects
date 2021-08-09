//
//  Expr.cpp
//  MSD6015
//
//  Created by Garret Wasden on 1/25/21.
//
#include <stdexcept>
#include <iostream>
#include "Expr.hpp"
#include "../Val/Val.hpp"
#include "../Env/Env.hpp"
#include "../Step/Step.hpp"
#include "../Cont/Cont.hpp"
#include "../pointer.h"

void Expr::pretty_print(std::ostream& stream){
    this->pretty_print_at(print_group_none,stream,0);
};

std::string Expr::to_string(){
  std::ostream output(nullptr);
  std::stringbuf strBuf;
  output.rdbuf(&strBuf);
  print(output);
  return strBuf.str();
};

std::string Expr::pp_to_string(){
  std::ostream output(nullptr);
  std::stringbuf strBuf;
  output.rdbuf(&strBuf);
  pretty_print(output);
  return strBuf.str();
};

PTR(Expr) Expr::parse(std::istream &in){
   PTR(Expr)e = parse_expr(in);
    return e;
    
}

PTR(Expr) Expr::parse_str(std::string s){
    std::istringstream is(s);
    return Expr::parse(is);
}

void Expr::consume(std::istream &in, int expect){
    int c = in.get();
    if (c != expect){
        throw std::runtime_error("consume mismatch");
    }
}

void Expr::skip_whitespace(std::istream &in) {
    while (1){
        int c = in.peek();
        if (!isspace(c)){
            break;
        }
        consume(in, c);
    }
}

PTR(Expr) Expr::parse_num(std::istream &in){
    int n = 0;
    bool negative = false;
    
    if(in.peek() == '-'){
        negative = true;
        consume(in, '-');
    }
    while(1) {
        int c = in.peek();
        if (isdigit(c)){
            consume(in,c);
            n = (unsigned)n*10 + (c-'0');
            if (n < 0){
                throw std::runtime_error("Int OverFlow");
            }
        } else
            break;
    }
    
    if (negative){
        n = -n;
    }
    return NEW(NumExpr)(n);
}

PTR(Expr) Expr::parse_inner(std::istream &in){
    skip_whitespace(in);
    int c = in.peek();
    if((c == '-') || isdigit(c)){
        return parse_num(in);
    }else if (c == '('){
        consume(in, '(');
        PTR(Expr) e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')'){
            throw std::runtime_error("Missing close parenthesis");
        }
        return e;
        
    }
    else if (isalpha(c)){
        PTR(Expr) e = parse_var(in);
        return e;
       
    }
    else if (c == '_'){
        PTR(Expr) e = parse_keyword(in);//-------------
        return e;
        
    }else{
        throw std::runtime_error("invalid input");
    }
}

PTR(Expr) Expr::parse_multicand(std::istream &in){
    PTR(Expr) expr = parse_inner(in);
    while(in.peek() == '('){
        consume(in, '(');
        PTR(Expr) actual_arg = parse_expr(in);
        consume(in,')');
        expr = NEW(CallExpr)(expr,actual_arg);
    }
    return expr;
};

PTR(Expr) Expr::parse_var(std::istream &in){
    std::string wantedString = "";
    while(1) {
        char c = in.peek();
        if (isalpha(c)){
            consume(in,c);
            std::string varString(1,c);
            wantedString = wantedString + varString;
        } else
            break;
    }
    return NEW(Variable)(wantedString);
}

PTR(Expr) Expr::parse_let(std::istream &in){
    PTR(Expr) lhs = parse_var(in);
    PTR(Variable) var = CAST(Variable)(lhs);
    skip_whitespace(in);
    int c = in.peek();
    if (c =='=') {
        consume(in, '=');
        PTR(Expr) rhs = parse_expr(in);
        PTR(Expr) body = parse_keyword(in);
        return NEW(LetExpr)(var, rhs, body);
    }else{
        throw std::runtime_error("input not correct let");
    }
}

PTR(Expr) Expr::parse_if(std::istream &in){
    PTR(Expr) lhs = parse_expr(in);
    PTR(Expr) test_part = CAST(Expr)(lhs);
    skip_whitespace(in);
    int c = in.peek();
    if (c =='_') {
        PTR(Expr) then_part = parse_keyword(in);
        PTR(Expr) else_part = parse_keyword(in);
        return NEW(IfExpr)(test_part, then_part, else_part);
    }else{
        throw std::runtime_error("input not correct if");
    }
}

PTR(Expr) Expr::parse_keyword(std::istream &in){
    skip_whitespace(in);
    consume(in, '_');
    int c = in.peek();
    if (c == 'l'){
        consume(in, 'l');
        consume(in, 'e');
        consume(in, 't');
        consume(in, ' ');
        return parse_let(in);
    }else if (c == 'i'){
        consume(in, 'i');
        c = in.peek();
        
        if (c == 'n'){
            consume(in, 'n');
            consume(in, ' ');
            return parse_expr(in);
            
        }else if (c == 'f'){
            consume(in, 'f');
            return parse_if(in);
        }else{
            throw std::runtime_error("input not correct");
        }
    }else if(c == 'f'){
        consume(in, 'f');
        c = in.peek();
        if (c == 'a'){
            consume(in, 'a');
            consume(in, 'l');
            consume(in, 's');
            consume(in, 'e');
            consume(in, ' ');
            return NEW(BoolExpr)(false);
        }else if(c == 'u'){
            consume(in, 'u');
            consume(in, 'n');
            return parse_fun(in);
        }else{
            throw std::runtime_error("input not correct");
        }
    }else if(c == 't'){
        consume(in, 't');
        c = in.peek();
        if(c == 'r'){
            consume(in, 'r');
            consume(in, 'u');
            consume(in, 'e');
            consume(in, ' ');
            return NEW(BoolExpr)(true);
        }else if(c == 'h'){
            consume(in, 'h');
            consume(in, 'e');
            consume(in, 'n');
            consume(in, ' ');
            return parse_expr(in);
        }else{
            throw std::runtime_error("input not correct");
        }
    }else if(c == 'e'){
        consume(in, 'e');
        consume(in, 'l');
        consume(in, 's');
        consume(in, 'e');
        consume(in, ' ');
        return parse_expr(in);
    }else {
        throw std::runtime_error("input not correct for let");
    }
}

PTR(Expr) Expr::parse_fun(std::istream &in){
    skip_whitespace(in);
    consume(in, '(');
    PTR(Expr) formal_arg = parse_var(in);
    PTR(Variable) var = CAST(Variable)(formal_arg);
    skip_whitespace(in);
    int c = in.peek();
    if (c ==')') {
        consume(in, ')');
        PTR(Expr) body = parse_expr(in);
        return NEW(FunExpr)(var->value,body);
    }else{
        throw std::runtime_error("input not correct");
    }
}


PTR(Expr) Expr::parse_addend(std::istream &in){
   PTR(Expr) e;
    
    e = parse_multicand(in);
    
    skip_whitespace(in);
    
    int c =  in.peek();
    if (c == '*') {
        consume(in, '*');
        PTR(Expr) rhs = parse_addend(in);
        return NEW(MultExpr)(e, rhs);
    }else{
        return e;
    }
}

PTR(Expr) Expr::parse_comparg(std::istream &in){
    PTR(Expr) e;
    
    e = parse_addend(in);
    
    skip_whitespace(in);
    
    int c =  in.peek();
    if (c == '+') {
        consume(in, '+');
        PTR(Expr) rhs = parse_comparg(in);
        return NEW(AddExpr)(e, rhs);
    }else{
        return e;
    }
}

PTR(Expr) Expr::parse_expr(std::istream &in){
    PTR(Expr) e;
    
    e = parse_comparg(in);
    
    skip_whitespace(in);
    
    int c =  in.peek();
    if (c == '=') {
        consume(in, '=');
        int c =  in.peek();
        if (c == '=') {
            consume(in, '=');
            PTR(Expr) rhs = parse_expr(in);
            return NEW(EqExpr)(e, rhs);
        }else{
            throw std::runtime_error("= charater not used correctly");
        }
    }else{
        return e;
    }
}

NumExpr::NumExpr(int value){
    this->value = value;
}

bool NumExpr::equals(PTR(Expr) e){
    PTR(NumExpr) e_num = CAST(NumExpr)(e);
    if (e_num == NULL){
        return false;
    }else{
        return this->value == e_num->value;
    }
};

PTR(Val) NumExpr::interp(PTR(Env) env){
    PTR(NumVal) val = NEW(NumVal)(this->value);
    return val;
}

void NumExpr::step_interp(){
    Step::mode = Step::continue_mode;
    Step::val = NEW(NumVal)(this->value);
    Step::cont = Step::cont;
}

bool NumExpr::has_variable(){
    return false;
}

PTR(Expr) NumExpr::subst(std::string value, PTR(Expr) e){
    return THIS;
}

void NumExpr::print(std::ostream& stream){
    stream << this->value;
}

void NumExpr::pretty_print_at(print_mode_t notationPriority, std::ostream &stream,  int lastNewLine){
    stream << this->value;
}

//constructor for BoolExpr
BoolExpr::BoolExpr(bool value){
    this->value = value;
}

bool BoolExpr::equals(PTR(Expr) e){
    PTR(BoolExpr) e_bool = CAST(BoolExpr)(e);
    if (e_bool == NULL){
        return false;
    }else{
        return this->value == e_bool->value;
    }
};

PTR(Val) BoolExpr::interp(PTR(Env) env){
    PTR(BoolVal) val = NEW(BoolVal)(this->value);
    return val;
}

void BoolExpr::step_interp(){
    Step::mode = Step::continue_mode;
    Step::val = NEW(BoolVal)(this->value);
    Step::cont = Step::cont;
}

bool BoolExpr::has_variable(){
    return false;
}

PTR(Expr) BoolExpr::subst(std::string value, PTR(Expr) e){
    return THIS;
}

void BoolExpr::print(std::ostream& stream){
    if (this->value == true){
        stream << "_true";
    }else{
        stream << "_false";
    }
}

void BoolExpr::pretty_print_at(print_mode_t notationPriority, std::ostream &stream,  int lastNewLine){
    stream << this->value;
}

//Constructor
Variable::Variable(std::string value){
    this->value = value;
}

//Equals based off of val
bool Variable::equals(PTR(Expr) e){
    PTR(Variable) e_var = CAST(Variable)(e);
    if (e_var == NULL){
        return false;
    }else{
        return this->value == e_var->value;
    }
};

//Returns a "runtime_error"
PTR(Val) Variable::interp(PTR(Env) env){
    return env->lookup(this->value);
}

void Variable::step_interp(){
    Step::mode = Step::continue_mode;
    Step::val = Step::env->lookup(this->value);
    Step::cont = Step::cont;
}

bool Variable::has_variable(){
    return true;
}

PTR(Expr) Variable::subst(std::string value, PTR(Expr) e){
    if (this->value.compare(value) != 0){
        return THIS;
    }else{
        return e;
    }
}
void Variable::print(std::ostream& stream){
    stream << this->value;
}

void Variable::pretty_print_at(print_mode_t notationPriority, std::ostream& stream,  int lastNewLine){
    stream << this->value;
}

//EqExpr constructor
EqExpr::EqExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

// Checks rhs and lhs Expr are the same
bool EqExpr::equals(PTR(Expr) e){
    PTR(EqExpr) e_Eq = CAST(EqExpr)(e);
    if (e_Eq == NULL){
        return false;
    } else {
        return this->lhs->equals(e_Eq->lhs) && this->rhs->equals(e_Eq->rhs);
    }
};

//Finds Val of both sides.
PTR(Val) EqExpr::interp(PTR(Env) env){
    PTR(Val) valLhs = this->lhs->interp(env);
    PTR(Val) valRhs = this->rhs->interp(env);
    if (valLhs->equals(valRhs)){
        return NEW(BoolVal)(true);
    }else{
        return NEW(BoolVal)(false);
    }
}

void EqExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env;
    Step::cont = NEW(RightThenEqCont)(rhs, Step::env, Step::cont);
}


// Checks if ether side has Variable
bool EqExpr::has_variable(){
    if (this->rhs->has_variable() || this->lhs->has_variable()){
        return true;
    }else{
        return false;
    }
}

//subs a string for an Expr
PTR(Expr) EqExpr::subst(std::string value, PTR(Expr) e){
    PTR(Expr) tempLhs = this->lhs->subst(value, e);
    PTR(Expr) tempRhs = this->rhs->subst(value, e);
    return NEW(EqExpr)(tempLhs, tempRhs);
}

//prints a inclean version of the expr to a string;
void EqExpr::print(std::ostream& stream){
    stream << "(";
    this->lhs->print(stream);
    stream << " == ";
    this->rhs->print(stream);
    stream << ")";
}

//prints a clean version of the expr to string;
void EqExpr::pretty_print_at(print_mode_t oldPriority, std::ostream& stream, int lastNewLine){
    bool LessOrEqual = this->notationPriority <= oldPriority && this->notationPriority!=0;
    bool inLet = (oldPriority == print_group_let);

    if (LessOrEqual && !inLet){
        stream << "(";
    }
    this->lhs->pretty_print_at(print_group_eq, stream, lastNewLine);
    stream << " == ";
    this->rhs->pretty_print_at(print_group_none, stream, lastNewLine);
    if (LessOrEqual && !inLet){
        stream << ")";
    }
}


//If Constructor
IfExpr::IfExpr(PTR(Expr) test_part, PTR(Expr) then_part, PTR(Expr) else_part){
    this->test_part = test_part;
    this->then_part = then_part;
    this->else_part = else_part;
}

bool IfExpr::equals(PTR(Expr) e){
    PTR(IfExpr) e_if = CAST(IfExpr)(e);
    if(e_if == NULL){
        return false;
    } else {
      return  (this->test_part->equals(e_if->test_part) &&
               this->then_part->equals(e_if->then_part) &&
               this->else_part->equals(e_if->else_part));
    }
}

PTR(Val) IfExpr::interp(PTR(Env) env){
    PTR(Val) test = this->test_part->interp(env);
    if(test->is_true()){
        return this->then_part->interp(env);
    }
    else{
        return this->else_part->interp(env);
    }
}

void IfExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = test_part;
    Step::env = Step::env;
    Step::cont = NEW(IfBranchCont)(then_part, else_part, Step::env, Step::cont);
}

bool IfExpr::has_variable(){
    if (this->test_part->has_variable() || this->then_part->has_variable() ||
        this->else_part->has_variable()){
        return true;
    }else{
        return false;
    }
}

PTR(Expr) IfExpr::subst(std::string value, PTR(Expr) e){
    PTR(Expr) tempTest = this->test_part->subst(value, e);
    PTR(Expr) tempThen = this->then_part->subst(value, e);
    PTR(Expr) tempElse = this->else_part->subst(value, e);
    return NEW(IfExpr)(tempTest, tempThen, tempElse);
}

void IfExpr::print(std::ostream& stream){
    stream << "(_if ";
    this->test_part->print(stream);
    stream << " _then ";
    this->then_part->print(stream);
    stream << " _else ";
    this->else_part->print(stream);
    stream << ")";
}

void IfExpr::pretty_print_at(print_mode_t oldPriority, std::ostream& stream , int lastNewLine){
    throw std::runtime_error("pretty print not working for _if");
}


//Add Constructor
AddExpr::AddExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

//Add equals base off the left and right vals
bool AddExpr::equals(PTR(Expr) e){
    PTR(AddExpr) e_add = CAST(AddExpr)(e);
    if (e_add == NULL){
        return false;
    } else {
        return this->lhs->equals(e_add->lhs) && this->rhs->equals(e_add->rhs);
    }
};

//Returns the Sum of the left and right vals
PTR(Val) AddExpr::interp(PTR(Env) env){
    PTR(Val) valLhs = this->lhs->interp(env);
    PTR(Val) valRhs = this->rhs->interp(env);
    valLhs = valLhs->add_to(valRhs);
    
    return (valLhs);
}

void AddExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env;
    Step::cont = NEW(RightThenAddCont)(rhs, Step::env, Step::cont);
}

// If the rhs or lhs has var returns false
bool AddExpr::has_variable(){
    if (this->rhs->has_variable() || this->lhs->has_variable()){
        return true;
    }else{
        return false;
    }
}

PTR(Expr) AddExpr::subst(std::string value, PTR(Expr) e){
    PTR(Expr) tempLhs = this->lhs->subst(value, e);
    PTR(Expr) tempRhs = this->rhs->subst(value, e);
    return NEW(AddExpr)(tempLhs, tempRhs);
}

void AddExpr::print(std::ostream& stream){
    
    stream << "(";
    this->lhs->print(stream);
    stream << "+";
    this->rhs->print(stream);
    stream << ")";
}

void AddExpr::pretty_print_at(print_mode_t oldPriority, std::ostream& stream, int lastNewLine){
    bool LessOrEqual = this->notationPriority <= oldPriority && this->notationPriority!=0;
    bool inLet = oldPriority == print_group_let;
    
    if (LessOrEqual && !inLet){
        stream << "(";
    }
    this->lhs->pretty_print_at(print_group_add, stream, lastNewLine);
    stream << " + ";
    this->rhs->pretty_print_at(print_group_eq, stream, lastNewLine);
    if (LessOrEqual && !inLet){
        stream << ")";
    }
}

//Constructor
MultExpr::MultExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

//compair based off the vals of the left and right
bool MultExpr::equals(PTR(Expr) e){
    PTR(MultExpr) e_mult = CAST(MultExpr)(e);
    if (e_mult == NULL){
        return false;
    } else {
        
        return this->lhs->equals(e_mult->lhs) && this->rhs->equals(e_mult->rhs);
    }
};

//Rerturns the product of the left and right
PTR(Val) MultExpr::interp(PTR(Env) env){
    PTR(Val) valLhs = this->lhs->interp(env);
    PTR(Val) valRhs = this->rhs->interp(env);
    valLhs = valLhs->mult_to(valRhs);
    
    return (valLhs);
}

void MultExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env;
    Step::cont = NEW(RightThenMultCont)(rhs, Step::env, Step::cont);
}

// If the rhs or lhs has var returns false
bool MultExpr::has_variable(){
    if (this->rhs->has_variable() || this->lhs->has_variable()){
        return true;
    }else{
        return false;
    }
}

PTR(Expr) MultExpr::subst(std::string value, PTR(Expr) e){
    PTR(Expr) tempLhs = this->lhs->subst(value, e);
    PTR(Expr) tempRhs = this->rhs->subst(value, e);
    return NEW(MultExpr)(tempLhs, tempRhs);
}
void MultExpr::print(std::ostream& stream){
    stream << "(";
    this->lhs->print(stream);
    stream << "*";
    this->rhs->print(stream);
    stream << ")";
}

void MultExpr::pretty_print_at(print_mode_t oldPriority, std::ostream& stream, int lastNewLine){
    bool LessOrEqual = this->notationPriority <= oldPriority && this->notationPriority!=0;
    bool inLet = oldPriority == print_group_let;

    if (LessOrEqual && !inLet){
        stream << "(";
    }
    this->lhs->pretty_print_at(print_group_add_or_mult, stream, lastNewLine);
    stream << " * ";
    this->rhs->pretty_print_at(print_group_add, stream, lastNewLine);
    if (LessOrEqual && !inLet){
        stream << ")";
    }
}

//Constructor
LetExpr::LetExpr(PTR(Variable) lhs, PTR(Expr) rhs, PTR(Expr) body){
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}

//compair based off the vals of the left and right
bool LetExpr::equals(PTR(Expr) e){
    PTR(LetExpr) e_let = CAST(LetExpr)(e);
    if (e_let == NULL){
        return false;
    } else {

        return this->lhs->equals(e_let->lhs) && this->rhs->equals(e_let->rhs);
    }
};

//Returns the product of the left and right
PTR(Val) LetExpr::interp(PTR(Env) env){
    PTR(Val) rhsValue = rhs->interp(env);
    PTR(Env) rhsEnv = NEW(ExtendedEnv)(this->lhs->value,rhsValue,env);
    return this->body->interp(rhsEnv);
}

void LetExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = Step::env;
    Step::cont = NEW(LetBodyCont)(this->lhs->value,body,Step::env,Step::cont);
}

// If the rhs or lhs has var returns false
bool LetExpr::has_variable(){
    if (this->rhs->has_variable() || this->body->has_variable()){
        return true;
    }else{
        return false;
    }
}

PTR(Expr) LetExpr::subst(std::string value, PTR(Expr) e){
    if ((lhs->value == (value))){
        PTR(Expr) tempRhs = this->rhs->subst(value, e);
        return NEW(LetExpr)(lhs,tempRhs,body);
    } else{
        PTR(Expr) tempBody = this->body->subst(value, e);
        PTR(Expr) tempRhs = this->rhs->subst(value, e);
        return NEW(LetExpr)(lhs,tempRhs,tempBody);
    }
}
void LetExpr::print(std::ostream& stream){
    stream << "(_let ";
    this->lhs->print(stream);
    stream << "=";
    this->rhs->print(stream);
    stream << " _in ";
    this->body->print(stream);
    stream << ")";
}

void LetExpr::pretty_print_at(print_mode_t oldPriority, std::ostream& stream , int lastNewLine){
    bool fromNone = (oldPriority <= 0);
    if (!fromNone){
        stream << "(";
    }
    
    long charTotal = stream.tellp();
    long spaceNeeded = charTotal - lastNewLine;
    stream << spaceNeeded;
    lastNewLine = (int)charTotal;
    stream << "_let ";
    this->lhs->pretty_print_at(print_group_let, stream,lastNewLine);
    stream << " = ";
    this->rhs->pretty_print_at(print_group_let, stream,lastNewLine);
    stream << "\n";
    
    stream << "_in  ";
    this->body->pretty_print_at(print_group_let, stream,lastNewLine);
    
    
    if (!fromNone){
        stream << ")";
    }
}


//FunExpr

//constructor for FunExpr;
FunExpr::FunExpr(std::string formal_arg, PTR(Expr) body){
    this->formal_arg = formal_arg;
    this->body = body;
}

bool FunExpr::equals(PTR(Expr) e){
    PTR(FunExpr) e_Fun = CAST(FunExpr)(e);
    if (e_Fun == NULL){
        return false;
    } else {
        return this->formal_arg == e_Fun->formal_arg && this->body->equals(e_Fun->body);
    }
}

PTR(Val) FunExpr::interp(PTR(Env) env){
    PTR(FunVal) fun = NEW(FunVal)(this->formal_arg, this->body, env);
    return fun;
}

void FunExpr::step_interp(){
    Step::mode = Step::continue_mode;
    Step::val = NEW(FunVal)(this->formal_arg, this->body, Step::env);
    Step::cont = Step::cont;
}

bool FunExpr::has_variable(){
    throw std::runtime_error("has_variable for FunExpr is no longer supported");
};

PTR(Expr) FunExpr::subst(std::string value, PTR(Expr) e){
    PTR(Expr) tempbody = this->body->subst(value, e);
    if (value == this->formal_arg){
        return NEW(FunExpr)(this->formal_arg, this->body);
    }
    return NEW(FunExpr)(this->formal_arg,tempbody);
};

void FunExpr::print(std::ostream& stream){
    stream << "(_fun(";
    stream << this->formal_arg;
    stream << ")";
    this->body->print(stream);
    stream << ")";
};

void FunExpr::pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine){
  
};

//CallExpr

//constructor for FunExpr;
CallExpr::CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg){
    this->to_be_called = to_be_called;
    this->actual_arg = actual_arg;
}

bool CallExpr::equals(PTR(Expr) e){
    PTR(CallExpr) e_Call = CAST(CallExpr)(e);
    if (e_Call == NULL){
        return false;
    } else {
        return this->to_be_called->equals(e_Call->to_be_called) && this->actual_arg->equals(e_Call->actual_arg);
    }
}

PTR(Val) CallExpr::interp(PTR(Env) env){
    return to_be_called->interp(env)->call(actual_arg->interp(env));
}

void CallExpr::step_interp(){
    Step::mode = Step::interp_mode;
    Step::expr = to_be_called;
    Step::cont = NEW(ArgThenCallCont)(actual_arg, Step::env, Step::cont);
}

bool CallExpr::has_variable(){
    throw std::runtime_error("has_variable for CallExpr is no longer supported");
};

PTR(Expr) CallExpr::subst(std::string value, PTR(Expr) e){
    PTR(Expr) tempTo_be_called = this->to_be_called->subst(value, e);
    
    PTR(CallExpr) call = NEW(CallExpr)(tempTo_be_called,this->actual_arg->subst(value,e));
    return call;
};

void CallExpr::print(std::ostream& stream){
    this->to_be_called->print(stream);
    stream << "(";
    this->actual_arg->print(stream);
    stream << ")";
};

void CallExpr::pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine){
  
};


