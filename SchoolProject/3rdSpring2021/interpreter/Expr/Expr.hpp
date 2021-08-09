//
//  Expr.hpp
//  MSD6015
//
//  Created by Garret Wasden on 1/25/21.
//

#ifndef Expr_hpp
#define Expr_hpp

#include "../catch.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "../pointer.h"

class Val;
class Env;
class Step;
class Cont;

CLASS(Expr){
public:
    typedef enum {
        print_group_none,
        print_group_eq,
        print_group_add,
        print_group_add_or_mult,
        print_group_let,
        print_group_if,
    } print_mode_t;
    
    
    print_mode_t notationPriority;
    virtual bool equals(PTR(Expr) e) = 0;
    virtual PTR(Val) interp(PTR(Env) env) = 0;
    virtual void step_interp() = 0;
    virtual bool has_variable() = 0;
    virtual PTR(Expr) subst(std::string value, PTR(Expr) e) = 0;
    virtual void print(std::ostream& stream) = 0;
    void pretty_print(std::ostream& stream);
    virtual void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine)=0;
    std::string to_string();
    std::string pp_to_string();
    
    static void consume(std::istream &in, int expect);
    static void skip_whitespace(std::istream &in);
    static PTR(Expr) parse_num(std::istream &in);
    static PTR(Expr) parse_str(std::string s);
    static PTR(Expr)parse_expr(std::istream &in);
    static PTR(Expr) parse_inner(std::istream &in);
    static PTR(Expr) parse_multicand(std::istream &in);
    static PTR(Expr) parse_addend(std::istream &in);
    static PTR(Expr) parse_var(std::istream &in);
    static PTR(Expr) parse_let(std::istream &in);
    static PTR(Expr) parse_if(std::istream &in);
    static PTR(Expr) parse_fun(std::istream &in);
    static PTR(Expr) parse_keyword(std::istream &in);
    static PTR(Expr) parse(std::istream &in);
    static PTR(Expr) parse_comparg(std::istream &in);
};

class NumExpr : public Expr {
public:
    int value;
    print_mode_t notationPriority = print_group_none;
    NumExpr(int val);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    void step_interp();
    bool has_variable();
    PTR(Expr) subst(std::string value, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
};

class BoolExpr : public Expr {
public:
    bool value;
    print_mode_t notationPriority = print_group_none;
    BoolExpr(bool val);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    void step_interp();
    bool has_variable();
    PTR(Expr) subst(std::string value, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
    
};

class Variable : public Expr {
public:
    std::string value;
    print_mode_t notationPriority = print_group_none;
    Variable (std::string val);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    void step_interp();
    bool has_variable();
    PTR(Expr) subst(std::string value, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
};
                               
class EqExpr : public Expr {
public:
   PTR(Expr) lhs;
   print_mode_t notationPriority = print_group_eq;
   PTR(Expr) rhs;
   EqExpr(PTR(Expr) lhs, PTR(Expr) rhs);
   bool equals(PTR(Expr) e);
   PTR(Val) interp(PTR(Env) env);
    void step_interp();
   bool has_variable();
   PTR(Expr) subst(std::string value, PTR(Expr) e);
   void print(std::ostream& stream);
   void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
};

class AddExpr : public Expr {
public:
    PTR(Expr) lhs;
    print_mode_t notationPriority = print_group_add;
    PTR(Expr) rhs;
    AddExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    void step_interp();
    bool has_variable();
    PTR(Expr) subst(std::string value, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
};

class MultExpr : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    print_mode_t notationPriority = print_group_add_or_mult;
    MultExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    void step_interp();
    bool has_variable();
    PTR(Expr) subst(std::string value, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
};

class LetExpr : public Expr {
public:
    PTR(Variable) lhs;
    PTR(Expr) rhs;
    PTR(Expr) body;
    print_mode_t notationPriority = print_group_let;
    LetExpr(PTR(Variable) lhs, PTR(Expr) rhs, PTR(Expr) body);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    void step_interp();
    bool has_variable();
    PTR(Expr) subst(std::string value, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
    
};

class IfExpr : public Expr {
public:
    PTR(Expr) test_part;
    PTR(Expr) then_part;
    PTR(Expr) else_part;
    //question this
    print_mode_t notationPriority = print_group_if;
    IfExpr(PTR(Expr) test_part, PTR(Expr) then_part, PTR(Expr) else_part);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    void step_interp();
    bool has_variable();
    PTR(Expr) subst(std::string value, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
    
};

class FunExpr: public Expr{
public:
    std::string formal_arg;
    PTR(Expr) body;
    
    print_mode_t notationPriority = print_group_let;//-----fix
    FunExpr(std::string formal_arg, PTR(Expr) body);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    void step_interp();
    bool has_variable();
    PTR(Expr) subst(std::string value, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
};

class CallExpr: public Expr{
public:
    PTR(Expr) to_be_called;
    PTR(Expr) actual_arg;
    
    print_mode_t notationPriority = print_group_let;//-----fix
    CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    void step_interp();
    bool has_variable();
    PTR(Expr) subst(std::string value, PTR(Expr) e);
    void print(std::ostream& stream);
    void pretty_print_at(print_mode_t notationPriority, std::ostream& stream, int lastNewLine);
};

#endif /* Expr_hpp */
