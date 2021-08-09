//
//  testGen.hpp
//  testGenerator
//
//  Created by Garret Wasden on 2/22/21.
//

#ifndef testGen_hpp
#define testGen_hpp

#include <stdio.h>
#include <iostream>
#include "exec.h"


class testGen {
public:
  int runTests(int argc, const char **argv);
private:
    std::string rand_expr_string();
    std::string rand_plus_string();
    std::string rand_mult_string();
    std::string rand_var_string();
    std::string rand_nonexpr_string();
    std::string rand_let_string();
    std::string rand_exprParth_string();
};
#endif /* testGen_hpp */
