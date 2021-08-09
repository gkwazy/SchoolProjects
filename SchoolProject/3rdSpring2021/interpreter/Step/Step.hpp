//
//  Step.hpp
//  MSD6015
//
//  Created by Garret Wasden on 4/8/21.
//

#ifndef Step_hpp
#define Step_hpp

#include <stdio.h>
#include "../pointer.h"

class Expr;
class Env;
class Val;
class Cont;

CLASS(Step){
public:
    typedef enum {
        interp_mode,
        continue_mode,
    } mode_t;
    
    static mode_t mode;
    static PTR(Expr) expr;
    static PTR(Env) env;
    static PTR(Val) val;
    static PTR(Cont) cont;
    
    static PTR(Val) interp_by_steps(PTR(Expr) e);
    
};

#endif /* Step_hpp */
