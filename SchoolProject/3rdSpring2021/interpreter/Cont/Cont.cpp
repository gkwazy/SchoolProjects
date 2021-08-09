//
//  Cont.cpp
//  MSD6015
//
//  Created by Garret Wasden on 4/8/21.
//

#include "Cont.hpp"
#include "../Step/Step.hpp"
#include "../Val/Val.hpp"
#include "../Env/Env.hpp"


PTR(Cont) Cont::done = NEW(DoneCont)();

//DoneCont::DoneCont(){
//}

void DoneCont::step_continue(){
    throw std::runtime_error("step_cont bad");
}

//bool DoneCont::equals(PTR(Cont) con){
//    PTR(Cont) con_if = CAST(Cont)(con);
//    if(con_if == NULL){
//        return false;
//    } else {
//        return true;
//    }
//}

RightThenAddCont::RightThenAddCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest){
    this->rhs = rhs;
    this->env = env;
    this->rest = rest;
};

void RightThenAddCont::step_continue(){
    PTR(Val) lhs_val = Step::val;
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = env;
    Step::cont = NEW(AddCont)(lhs_val, rest);
};
//bool RightThenAddCont::equals(PTR(Cont) con){
//    PTR(Cont) con_if = CAST(Cont)(con);
//    if(con_if == NULL){
//        return false;
//    } else {
//        this->rhs;
//        this->env;
//        this->rest;
//    }
//}

AddCont::AddCont(PTR(Val) val, PTR(Cont)rest){
    this->lhs_val = val;
    this->rest = rest;
}

void AddCont::step_continue(){
    PTR(Val) rhs_val = Step::val;
    Step::mode = Step::continue_mode;
    Step::val = lhs_val->add_to(rhs_val);
    Step::cont = rest;
    
};

RightThenMultCont::RightThenMultCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest){
    this->rhs = rhs;
    this->env = env;
    this->rest = rest;
};

void RightThenMultCont::step_continue(){
    PTR(Val) lhs_val = Step::val;
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = env;
    Step::cont = NEW(MultCont)(lhs_val, rest);
    
};

MultCont::MultCont(PTR(Val) val, PTR(Cont)rest){
    this->lhs_val = val;
    this->rest = rest;
}

void MultCont::step_continue(){
    PTR(Val) rhs_val = Step::val;
    Step::mode = Step::continue_mode;
    Step::val = lhs_val->mult_to(rhs_val);
    Step::cont = rest;
    
};

RightThenEqCont::RightThenEqCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest){
    this->rhs = rhs;
    this->env = env;
    this->rest = rest;
};

void RightThenEqCont::step_continue(){
    PTR(Val) lhs_val = Step::val;
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = env;
    Step::cont = NEW(EqCont)(lhs_val, rest);
    
};

EqCont::EqCont(PTR(Val) val, PTR(Cont)rest){
    this->lhs_val = val;
    this->rest = rest;
}

void EqCont::step_continue(){
    PTR(Val) rhs_val = Step::val;
    Step::mode = Step::continue_mode;
    Step::val = NEW(BoolVal)(lhs_val->equals(rhs_val));
    Step::cont = rest;
    
};

IfBranchCont::IfBranchCont(PTR(Expr) then_part,PTR(Expr) else_part, PTR(Env) env,PTR(Cont) rest){
    this->then_part = then_part;
    this->else_part = else_part;
    this->env = env;
    this->rest = rest;
};

void IfBranchCont::step_continue(){
    PTR(Val) test_val = Step::val;
    Step::mode = Step::interp_mode;
    if ( test_val->is_true()){
        Step::expr = then_part;
    }else{
        Step::expr = else_part;
    }
    Step::env = env;
    Step::cont = rest;
}

LetBodyCont::LetBodyCont(std::string var, PTR(Expr) body, PTR(Env) env, PTR(Cont) rest){
    this->var = var;
    this->body = body;
    this->env = env;
    this->rest = rest;
}

void LetBodyCont::step_continue(){
    Step::mode = Step::interp_mode;
    Step::expr = body;
    Step::env = NEW(ExtendedEnv)(var, Step::val, env);
    Step::cont = rest;
}

CallCont::CallCont(PTR(Val) to_be_called_val, PTR(Cont) rest){
    this->to_be_called_val = to_be_called_val;
    this->rest = rest;
}

void CallCont::step_continue(){
    to_be_called_val->call_step(Step::val, rest);
}

ArgThenCallCont::ArgThenCallCont(PTR(Expr) actural_arg, PTR(Env) env, PTR(Cont) rest){
    this->actural_arg = actural_arg;
    this->env = env;
    this->rest = rest;
}

void ArgThenCallCont::step_continue(){
    Step::mode = Step::interp_mode;
    Step::expr = actural_arg;
    Step::env = env;
    Step::cont = NEW(CallCont)(Step::val,rest);
}
