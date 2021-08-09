//
//  cmdline.cpp
//  msdscript
//
//  Created by Garret Wasden on 1/19/21.
//
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <string>
#include "cmdline.hpp"
#include "../catch.h"
#include "../Expr/Expr.hpp"
#include "../Val/Val.hpp"
#include "../Env/Env.hpp"
#include "../Step/Step.hpp"
#include "../Cont/Cont.hpp"
 
 
std::string runCommand(std::string command, std::string input){
    std::string myReturn;
    std::istringstream is(input);
   if (command.compare("--interp")){
        PTR(Expr) e = Expr::parse_expr(is);
        PTR(Val) v = e->interp(EmptyEnv::empty);
       myReturn = v->to_expr()->to_string();


    }else if (command.compare("--step")){
        PTR(Expr) e = Expr::parse_expr(is);
        PTR(Val) v = Step::interp_by_steps(e);
        myReturn = v->to_expr()->to_string();


    }else if (command.compare("--print")){
        PTR(Expr) e = Expr::parse_expr(is);
        myReturn = e->to_string();
    }
    return myReturn;
}

void use_arguments(int lenght,char ** command)
{
    std::string helpMessage = "list of commands \n --test - runs test on project, can only be ran once\n and that is it for now. Sorry\n";
    bool untested = true;
    
    for (int i = 1; i < lenght; i++) {
        std::string wantedCommand = command[i];
        if (wantedCommand == "--help"){
            std::cout<< helpMessage;
            exit(0);
        }else if (wantedCommand == "--interp"){
            PTR(Expr) e = Expr::parse_expr(std::cin);
            PTR(Val) v = e->interp(EmptyEnv::empty);
            std::string s = v->to_expr()->to_string();
            std::cout << s;
          
        }else if (wantedCommand == "--step"){
            PTR(Expr) e = Expr::parse_expr(std::cin);
            PTR(Val) v = Step::interp_by_steps(e);
            std::string s = v->to_expr()->to_string();
            std::cout << s;
          
        }else if (wantedCommand == "--print"){
            PTR(Expr) e = Expr::parse_expr(std::cin);
           std::cout << e->to_string();
          
        }
//        else if (wantedCommand == "--pretty-print"){
//            PTR(Expr) e = Expr::parse_expr(std::cin);
//           std::cout << e->pp_to_string();
//
//        }
        else if (wantedCommand == "--test"){
            if (untested){
                untested = false;
                int result =Catch::Session().run(1, command);
                if ( result != 0){
                    exit(1);
                };
            }
            else{
                std::cerr << "Tests already run\n";
                exit(1);
            }
        }
        else{
            std::cerr << "Unknown Command\n";
            exit(1);
        }
    }
};
