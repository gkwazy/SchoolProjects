//
//  Step.cpp
//  MSD6015
//
//  Created by Garret Wasden on 4/8/21.
//

#include "Step.hpp"
#include "../pointer.h"
#include "../Env/Env.hpp"
#include "../Cont/Cont.hpp"
#include "../Expr/Expr.hpp"
#include "../Val/Val.hpp"


Step::mode_t Step::mode;
PTR(Expr) Step::expr;
PTR(Env) Step::env;
PTR(Val) Step::val;
PTR(Cont) Step::cont;

PTR(Val) Step::interp_by_steps(PTR(Expr) e){
    Step::mode = Step::interp_mode;
    Step::expr = e;
    Step::env = Env::empty;
    Step::val = nullptr;
    Step::cont = Cont::done;
    
    while (1){
        if (Step::mode == Step::interp_mode){
            Step::expr->step_interp();
        }else{
            if (Step::cont == Cont::done){
                return Step::val;
            }else{
                Step::cont->step_continue();
            }
        }
    }
}



