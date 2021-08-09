//
//  testGen.cpp
//  testGenerator
//
//  Created by Garret Wasden on 2/22/21.
//

#include "testGen.hpp"
#include <stdio.h>
#include <iostream>
#include "exec.h"



int testGen::runTests(int argc, const char **argv) {
    const char *argument1 = argv[1];
    const char *argument2;
    if ( argc > 2){
       argument2 = argv[2];
    }
    else{
        argument2 = argv[1];
    }
    const char * const interp_argv[] = { argument1, "--interp"};
    const char * const print_argv[] = { argument2, "--print"};

    for ( int i = 0; i < 100; i++){
        std::string in = rand_expr_string();
        std::cout << "Trying --- " << in << "\n";

        ExecResult interp_results = exec_program(2, interp_argv, in);
        ExecResult print_results = exec_program(2, print_argv, in);

        ExecResult interp_again_results = exec_program(2, interp_argv, print_results.out);
        if (interp_again_results.out != interp_results.out){
            std::cout << "results--- "<< in << "\n";
            throw std::runtime_error("different results for printed\n");
        }
    }
    return 0;
}

 std::string testGen::rand_expr_string(){
     srand((int)clock());
     if (rand() % 10 < 6){
         return std::to_string(rand());
     }
     else{
         return rand_nonexpr_string();
     }
};

std::string testGen::rand_nonexpr_string(){
    srand((int)clock());
    int randNumber =rand() % 10;
    if (randNumber < 2){
        return rand_var_string();
    }
    else if (randNumber < 4){
        return rand_plus_string();
    }
    else if (randNumber < 6){
        return rand_mult_string();
    }
    else if (randNumber < 8){
        return rand_exprParth_string();
    }
    else{
        return rand_let_string();
    }
};

std::string testGen::rand_exprParth_string(){
    return "(" + rand_expr_string() + ")";
};

std::string testGen::rand_var_string(){
    char c;
    int random;

    srand((int)clock());
    random = rand() % 26;
    c = 'a' + random;
    std::string s(1, c);
    return s;
}

std::string testGen::rand_plus_string(){
    return rand_expr_string() + " + " + rand_expr_string();
}

std::string testGen::rand_mult_string(){
    return rand_expr_string() + " * " + rand_expr_string();
}

std::string testGen::rand_let_string(){
    std::string workingString = "_let " + rand_var_string() + " = " + rand_expr_string() + " _in  " + rand_expr_string();
    return workingString;
}


