//
//  Cont.hpp
//  MSD6015
//
//  Created by Garret Wasden on 4/8/21.
//

#ifndef Cont_hpp
#define Cont_hpp

#include <stdio.h>
#include "../pointer.h"
#include <string>

class Val;
class Step;
class Expr;
class Env;

CLASS(Cont){
public:
    virtual void step_continue() = 0;
    static PTR(Cont) done;
//    virtual bool equals(PTR(Cont) con) = 0;
};

class DoneCont : public Cont{
public:
//    DoneCont();
    void step_continue();
//    bool equals(PTR(Cont) con);
};

class RightThenAddCont : public Cont {
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    RightThenAddCont(PTR(Expr) newrhs, PTR(Env) newenv, PTR(Cont) newrest);
    void step_continue();
};

class AddCont : public Cont{
    public:
    PTR(Val) lhs_val;
    PTR(Cont)rest;
    
    AddCont(PTR(Val) val, PTR(Cont)rest);
    void step_continue();
//    bool equals(PTR(Cont) con);
};

class RightThenMultCont : public Cont {
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    RightThenMultCont(PTR(Expr) newrhs, PTR(Env) newenv, PTR(Cont) newrest);
    void step_continue();
//    bool equals(PTR(Cont) con);
};

class MultCont : public Cont{
    public:
    PTR(Val) lhs_val;
    PTR(Cont)rest;
    
    MultCont(PTR(Val) val, PTR(Cont)rest);
    void step_continue();
//    bool equals(PTR(Cont) con);
};

class RightThenEqCont : public Cont {
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    RightThenEqCont(PTR(Expr) newrhs, PTR(Env) newenv, PTR(Cont) newrest);
    void step_continue();
//    bool equals(PTR(Cont) con);
};

class EqCont : public Cont{
    public:
    PTR(Val) lhs_val;
    PTR(Cont)rest;
    
    EqCont(PTR(Val) val, PTR(Cont)rest);
    void step_continue();
//    bool equals(PTR(Cont) con);
};


class IfBranchCont : public Cont{
    public:
    PTR(Expr) then_part;
    PTR(Expr) else_part;
    PTR(Env) env;
    PTR(Cont) rest;
    
    IfBranchCont(PTR(Expr) then_part,PTR(Expr) else_part, PTR(Env) env,PTR(Cont) rest);
    void step_continue();
//    bool equals(PTR(Cont) con);
};

class LetBodyCont : public Cont{
public:
    std::string var;
    PTR(Expr) body;
    PTR(Env) env;
    PTR(Cont) rest;
    
    LetBodyCont(std::string var, PTR(Expr) body, PTR(Env) env, PTR(Cont) rest);
    void step_continue();
//    bool equals(PTR(Cont) con);
};

class ArgThenCallCont : public Cont{
public:
    PTR(Expr) actural_arg;
    PTR(Env) env;
    PTR(Cont) rest;
    
    ArgThenCallCont( PTR(Expr) actural_arg, PTR(Env) env, PTR(Cont) rest);
    void step_continue();
//    bool equals(PTR(Cont) con);
};

class CallCont : public Cont {
public:
    PTR(Val) to_be_called_val;
    PTR(Cont) rest;
    
    CallCont(PTR(Val) to_be_called_val, PTR(Cont) rest);
    void step_continue();
//    bool equals(PTR(Cont) con);
};

#endif /* Cont_hpp */
