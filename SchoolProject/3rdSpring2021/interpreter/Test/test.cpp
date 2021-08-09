//
//  test.cpp
//  MSD6015
//
//  Created by Garret Wasden on 3/1/21.
//

#include "test.hpp"
#include "../catch.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "../Val/Val.hpp"
#include "../Expr/Expr.hpp"
#include "../Env/Env.hpp"
#include "../Step/Step.hpp"
#include "../pointer.h"

PTR(Val) testInterp(std::string str){
    PTR(Expr) Estr = Expr::parse_str(str);
    PTR(Val) val = Estr->interp(Env::empty);
    return val;
};

PTR(Expr) testExpr(std::string str){
    PTR(Expr) Estr = Expr::parse_str(str);
    return Estr;
};

TEST_CASE("equals"){
    //Variables for Testing
    PTR(NumExpr) num3 = NEW(NumExpr)(3);
    PTR(NumExpr) num3copy = NEW(NumExpr)(3);
    PTR(NumExpr) num2copy = NEW(NumExpr)(2);
    PTR(NumExpr) num2 = NEW(NumExpr)(2);
    PTR(NumExpr) num4 = NEW(NumExpr)(4);
    PTR(NumExpr) num5 = NEW(NumExpr)(5);
    PTR(NumExpr) num9 = NEW(NumExpr)(9);

    //Var variables
    PTR(Variable) numX = NEW(Variable)("X");
    PTR(Variable) numY = NEW(Variable)("Y");
    PTR(Variable) numXcopy = NEW(Variable)("X");
    
    //BoolExNEW(
    PTR(BoolExpr) exprTrue = NEW(BoolExpr)(true);
    PTR(BoolExpr) exprFalse =NEW(BoolExpr)(false);
    
    //Eq Variables
    PTR(EqExpr)eq3_2 = NEW(EqExpr)(num3, num2);
    PTR(EqExpr)eq3_3 = NEW(EqExpr)(num3, num3);
    PTR(EqExpr)eq3_x = NEW(EqExpr)(num3, numX);
    PTR(EqExpr)eq3_add3_x = NEW(EqExpr)(num3, NEW(AddExpr)(num3,numX));
    PTR(EqExpr)eqadd3_2_mult3_2 = NEW(EqExpr)(NEW(AddExpr)(num3,num2),NEW(MultExpr)(num3,num2));
    PTR(EqExpr)eqadd3_x_mult3_x = NEW(EqExpr)(NEW(AddExpr)(num3,numX),NEW(MultExpr)(num3,numX));
    
    //Val NumVal
    
   PTR(NumVal) valn2 = NEW(NumVal)(2);
   PTR(NumVal) valn3 = NEW(NumVal)(3);
   PTR(NumVal) valn5 = NEW(NumVal)(5);
   PTR(NumVal) valn6 = NEW(NumVal)(6);
    PTR(NumVal)valn14 = NEW(NumVal)(14);
    
    //Val BoolVals
    PTR(BoolVal) valbFalse = NEW(BoolVal)(false);


    //Add Variables
    PTR(AddExpr) add3_3 = NEW(AddExpr)(num3,num3);
    PTR(AddExpr) add3_2 = NEW(AddExpr)(num3,num2);
    PTR(AddExpr) add3_x = NEW(AddExpr)(num3,numX);
    PTR(AddExpr) addx_x = NEW(AddExpr)(numX,numX);
    PTR(AddExpr) add1_2_3 = NEW(AddExpr)(NEW(NumExpr)(1), NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)));
    PTR(AddExpr) add1a2_3 = NEW(AddExpr)(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(NumExpr)(3));
    PTR(AddExpr) add1_2m3 = NEW(AddExpr)(NEW(NumExpr)(1), NEW(MultExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)));
    
    //Mult variables
    PTR(MultExpr)mult3_2 = NEW(MultExpr)(num3,num2);
    PTR(MultExpr)mult1a2_3 = NEW(MultExpr)(NEW(AddExpr)(NEW(NumExpr)(1), NEW(NumExpr)(2)), NEW(NumExpr)(3));
    PTR(MultExpr)mult1_2a3 = NEW(MultExpr)(NEW(NumExpr)(1),NEW(AddExpr)( NEW(NumExpr)(2), NEW(NumExpr)(3)));
    PTR(MultExpr)mult3m2_3a2 = NEW(MultExpr)(mult3_2,add3_2);
    

    
    //Let variables
    PTR(LetExpr) letx_5 = NEW(LetExpr)(numX,num5, NEW(Variable)("X"));
    PTR(LetExpr) letx_9add5_x = NEW(LetExpr)(numX, num9, NEW(AddExpr)(num5, numX));
    PTR(LetExpr) letx_5letx_9add5_x = NEW(LetExpr)(numX,num5,
                                      NEW(LetExpr)(numX,num9,
                                              NEW(AddExpr)(num5,numX)));
    PTR(LetExpr) letx_5addlety_3addy_2_x = NEW(LetExpr)(numX,num5,
                                      NEW(AddExpr)(NEW(LetExpr)(numY,num3,
                                        NEW(AddExpr)(numY, num2)),numX));

    PTR(LetExpr) letz_Add0_2_Addz_32 = NEW(LetExpr)(NEW(Variable)("z"), NEW(AddExpr)(NEW(NumExpr)(0),NEW(NumExpr)(2)),NEW(AddExpr)(NEW(Variable)("z"),NEW(NumExpr)(32)));
    
    PTR(LetExpr) let4 = NEW(LetExpr)(NEW(Variable)("z"), NEW(AddExpr)(NEW(Variable)("z"),NEW(NumExpr)(2)),NEW(AddExpr)(NEW(Variable)("z"),NEW(NumExpr)(32)));
    
// If Variable
    PTR(IfExpr) ft3_5 = NEW(IfExpr)(exprTrue,num3,num5);
    PTR(IfExpr) feqf3_5 = NEW(IfExpr)(NEW(EqExpr)(num3,num4),num3,num5);
    PTR(EqExpr) eq3_4 = NEW(EqExpr)(num3,num4);
    
//Fun/Call Variable
   PTR(FunExpr) funx_ax_3 = NEW(FunExpr)("X", NEW(AddExpr)(NEW(Variable)("X"),NEW(NumExpr)(3)));
    PTR(MultExpr) multx_x = NEW(MultExpr)(numX,numX);
    
    PTR(MultExpr) multy_y = NEW(MultExpr)(numY,numY);
    
    PTR(AddExpr) addmx_x_my_y = NEW(AddExpr)(multx_x, multy_y);
    PTR(FunVal) funval = NEW(FunVal)("X", add3_x,Env::empty);
    PTR(FunVal) funvalx = NEW(FunVal)("X", addx_x,Env::empty);
    
    PTR(FunExpr) funy_mx_xamy_y = NEW(FunExpr)("Y", addmx_x_my_y);
    PTR(FunExpr) funx_funy_mx_xamy_y = NEW(FunExpr)("X", funy_mx_xamy_y);
    
    PTR(CallExpr) callax_3x = NEW(CallExpr)(funx_ax_3, NEW(NumExpr)(2));
    PTR(CallExpr) callax_3y = NEW(CallExpr)(funx_ax_3, NEW(Variable)("Y"));
    
    std::string letffunx_funy_mx_xamy_y = "_let y = 8 _in _let f = _fun (x) x*y _in f(2)";
    
    std::string letf = "_fun (x) x*y";
    
    std::string factrlF = "_let factrl = _fun (factrl) _fun (x) _if x == 1 _then 1 _else x * factrl(factrl)(x + -1) _in factrl(factrl)(10)";
    
    std::string testing = "_if 8 == 1 _then 1 _else 4 ";
    std::string testone = "1==1";
    std::string funx_mx_4 = "_let f = _fun(x) _fun(y) x+y _in (f(5)(1))";
     
   
//Fun/Call Test
    CHECK(callax_3x->interp(Env::empty)->equals(valn5) == true);
    CHECK(callax_3y->to_string() == "(_fun(X)(X+3))(Y)");
    CHECK(callax_3y->subst("x", num5)->to_string() == "(_fun(X)(X+3))(Y)");

    CHECK(testInterp(testone)->to_expr()->to_string() == "_true");
    CHECK(testInterp(testing)->to_expr()->to_string() == "4");
    CHECK(testInterp(funx_mx_4)->to_expr()->to_string() == "6");
    CHECK(testInterp(letffunx_funy_mx_xamy_y)->to_expr()->to_string() == "16");
    CHECK(testInterp(factrlF)->to_expr()->to_string() == "3628800");
    CHECK(funx_ax_3->to_string() == "(_fun(X)(X+3))");
    CHECK(funx_funy_mx_xamy_y->to_string() == "(_fun(X)(_fun(Y)((X*X)+(Y*Y))))");
    CHECK(funx_ax_3->equals(funx_ax_3) == true);
    CHECK(funval->to_expr()->to_string() == "(_fun(X)(3+X))");
    CHECK(funval->call(valn5)->to_expr()->to_string()=="8");
    CHECK(funvalx->to_expr()->to_string() == "(_fun(X)(X+X))");
    CHECK(funvalx->call(valn5)->to_expr()->to_string()=="10");
    CHECK_THROWS_WITH( funval->is_true(), "is_true of Functions" );
    CHECK_THROWS_WITH( funval->mult_to(valn5),"Mult of Functions" );
    CHECK_THROWS_WITH( funval->add_to(valn5), "add of Functions" );
    
    
    

//If Test
    CHECK(ft3_5->interp(Env::empty)->to_expr()->to_string() == "3");
    CHECK(ft3_5->interp(Env::empty)->equals(valn3) == true);
    CHECK(feqf3_5->interp(Env::empty)->equals(valn5) == true);
    CHECK(eq3_4->interp(Env::empty)->to_expr()->to_string() == "_false");
    CHECK(Expr::parse_str("(_if 3==5 _then 8 _else 6)")->interp(Env::empty)->equals(valn6));
    CHECK(Expr::parse_str("(_if 3==5 _then 8 _else 5)")->equals(Expr::parse_str("(_if 3==5 _then 8 _else 5)")) == true);
    CHECK(Expr::parse_str("(_if 3==5 _then 8 _else 5)")->has_variable() == false);
    CHECK(Expr::parse_str("(_if x==5 _then 8 _else 5)")->has_variable() == true);
    CHECK(Expr::parse_str("(_if x==5 _then 8 _else 5)")->subst("X", numX)->equals(Expr::parse_str("(_if x==5 _then 8 _else 5)")) == true);
    CHECK(Expr::parse_str("(_if x==5 _then 8 _else 5)")->subst("X", numX)->equals(Expr::parse_str("(_if x==5 _then 8 _else 5)")) == true);
    
    CHECK(Expr::parse_str("(_if x==5 _then 8 _else 5)")->to_string() == "(_if (x == 5) _then 8 _else 5)");

    CHECK_THROWS_WITH(Expr::parse_str("(_ifj 4==5 _then 8 _else 7)"),"input not correct if");


    //Num Tests
    //-equals test
    CHECK( (NEW(NumExpr)(3))->equals (NEW(NumExpr)(3)) == true);
    CHECK( (NEW(NumExpr)(3))->equals (NEW(NumExpr)(4)) == false);
    CHECK( (num3)-> equals (num3copy) == true);
    CHECK( (num3)->equals (num3) == true);
    CHECK(num3-> equals(numX)==false);

    //-interp tests
    CHECK((num3->interp(Env::empty))->equals(valn3)); //3
    CHECK((NEW(NumExpr)(6))->interp(Env::empty)->equals(valn6)); //6

    //has_variable test
    CHECK((NEW(NumExpr)(6))->has_variable() == false);
    CHECK(num3 ->has_variable() == false);

    //subst test
    CHECK(num3 ->subst("x", NEW(NumExpr)(6))->equals(num3) == true);
    //tostring & pp_to_string test
    CHECK(num3 ->to_string() == "3");
    CHECK(num3 ->pp_to_string() == "3");


// Variable Testing
    //equals tests
    CHECK( (numX)-> equals (numX) == true);
    CHECK( (numX)->equals (numY) == false);
    CHECK( (numX)-> equals (numXcopy) == true);
    //interp test
    CHECK_THROWS_WITH( (new Variable("X"))->interp(Env::empty), "free variable: X" );
    //has_variable
    CHECK((NEW(Variable)("x"))->has_variable() == true);
    CHECK(numX ->has_variable() == true);
    //subst test
    CHECK(numX ->subst("X", NEW(NumExpr)(3))->equals(num3) == true);
    CHECK(numX ->subst("Y", NEW(NumExpr)(3))->equals(num3) == false);
    CHECK(numX ->subst("x", NEW(NumExpr)(3))->equals(num3) == false);
    CHECK(numX ->subst("x", NEW(Variable)("Y"))->equals(numY) == false);
    //tostring and pp_to_string test
    CHECK(numX ->to_string() == "X");
    CHECK(numX ->pp_to_string() == "X");


//Eq Test
    //constructor tests
    CHECK((eq3_2)-> equals (eq3_2) == true);
    CHECK((eq3_3)-> equals (eq3_2) == false);
    CHECK(eqadd3_2_mult3_2->equals(eqadd3_2_mult3_2)== true);

    //has_variable test
    CHECK(eq3_3->has_variable() == false);
    CHECK(eq3_x->has_variable() == true);
    CHECK(eqadd3_2_mult3_2->has_variable() == false);
    CHECK(eqadd3_x_mult3_x->has_variable() == true);

    //subst test
    CHECK(eq3_x->subst("X", num3)->equals(eq3_3));
    CHECK(eqadd3_x_mult3_x->subst("X", num2)->equals(eqadd3_2_mult3_2));

    //print test
    CHECK(eq3_3->to_string() == "(3 == 3)");
    CHECK(eq3_x->to_string() == "(3 == X)");
    CHECK(eqadd3_x_mult3_x->to_string() == "((3+X) == (3*X))");

    //pretty print test
    CHECK(eq3_3->pp_to_string() == "3 == 3");
    CHECK(eq3_x->pp_to_string() == "3 == X");
    CHECK(eqadd3_x_mult3_x->pp_to_string() == "3 + X == 3 * X");
    CHECK(eq3_add3_x->pp_to_string() == "3 == 3 + X");


//BoolExpr test
    CHECK(exprTrue->to_string() == "_true" );
    CHECK(exprFalse->to_string() == "_false" );
    CHECK(exprTrue->equals(exprTrue) == true);
    CHECK(exprTrue->equals(exprFalse) == false);
    CHECK(exprTrue->equals(num2) == false);
    CHECK(exprTrue->equals(exprFalse) == false);
    CHECK(exprTrue->has_variable()== false);
    CHECK(exprTrue->subst("x",num2)->equals(exprTrue) == true);



// Val Test
    CHECK(valn2->equals(NEW(NumVal)(2)) == true);
    CHECK(valn2->equals(valn3) == false);
    CHECK(valn2->equals(NEW(BoolVal)(true)) == false);
    CHECK(valbFalse->equals(NEW(BoolVal)(false))== true);
    CHECK(valbFalse->equals(NEW(BoolVal)(true))== false);
    CHECK(valn2->add_to(valn3)->equals(NEW(NumVal)(5)));



//Add Tests
    //equals tests
    CHECK( (NEW(AddExpr)(num3,num3))->equals (NEW(AddExpr)(num3,num3)) == true);
    CHECK( (NEW(AddExpr)(num3,num2))->equals (NEW(AddExpr)(num3,num2)) == true);
    CHECK( (NEW(AddExpr)(num2,num3))->equals (NEW(AddExpr)(num3,num2)) == false);
    CHECK( (NEW(AddExpr)(num3,num2))->equals (NEW(AddExpr)(num4,num5)) == false);
    CHECK( (NEW(AddExpr)(num3,num2))->equals (NEW(AddExpr)(num3copy,num2copy)) == true);
    CHECK (add3_3->equals(numX)==false);

    //interp test
    CHECK( (NEW(AddExpr)(num3,num2))->interp(Env::empty)->to_expr()->to_string() =="5");

    CHECK( (NEW(AddExpr)(num3,num2))->interp(Env::empty)->equals(NEW(NumVal)(5)));
    CHECK( (NEW(AddExpr)(num3,num3))->interp(Env::empty)->equals(valn6)); //6-------
    CHECK( (NEW(AddExpr)(num3,num3copy))->interp(Env::empty)->equals(valn6));//6 ------
    CHECK( (NEW(AddExpr)(num3,num2))->interp(Env::empty)->equals(num5->interp(Env::empty)));

    CHECK_THROWS_WITH( (NEW(AddExpr)(num3,numX))->interp(Env::empty), "free variable: X" );

    //has_variable test
    CHECK( (NEW(AddExpr)(num3,num3))->has_variable() == false);
    CHECK( (NEW(AddExpr)(num3,numX))->has_variable() == true);
    CHECK( (NEW(AddExpr)(numX,numY))->has_variable() == true);

    //subst test
    CHECK( (NEW(AddExpr)(NEW(Variable)("x"), NEW(NumExpr)(7)))
           ->subst("x", NEW(Variable)("y"))
           ->equals(NEW(AddExpr)(NEW(Variable)("y"), NEW(NumExpr)(7))) == true );
    CHECK( (NEW(AddExpr)(NEW(Variable)("a"), NEW(NumExpr)(7)))
           ->subst("x", NEW(Variable)("y"))
           ->equals(NEW(AddExpr)(NEW(Variable)("a"), NEW(NumExpr)(7))) == true );
    CHECK( (NEW(AddExpr)(NEW(NumExpr)(9), NEW(NumExpr)(7)))
           ->subst("x", NEW(Variable)("y"))
           ->equals(NEW(AddExpr)(NEW(NumExpr)(9), NEW(NumExpr)(7))) == true );
    CHECK( (NEW(AddExpr)(NEW(Variable)("x"), NEW(Variable)("x")))
           ->subst("x", NEW(Variable)("y"))
           ->equals(NEW(AddExpr)(NEW(Variable)("y"), NEW(Variable)("y"))) == true );

    //tostring
    CHECK(add3_2->to_string() == "(3+2)");
    CHECK(add1_2_3->pp_to_string() == "1 + 2 + 3");
    CHECK(add1a2_3->pp_to_string() == "(1 + 2) + 3");
    CHECK(add1_2m3->pp_to_string() == "1 + 2 * 3");



//Mult Test
    //equals test
    CHECK( (NEW(MultExpr)(num3,num3))->equals (NEW(MultExpr)(num3,num3)) == true);
    CHECK( (NEW(MultExpr)(num3,num2))->equals (NEW(MultExpr)(num3,num2)) == true);
    CHECK( (NEW(MultExpr)(num2,num3))->equals (NEW(MultExpr)(num3,num2)) == false);
    CHECK( (NEW(MultExpr)(num3,num2))->equals (NEW(MultExpr)(num4,num5)) == false);
    CHECK( (NEW(MultExpr)(num3,num2))->equals (NEW(MultExpr)(num3copy,num2copy)) == true);
    CHECK (mult3_2->equals(numX)==false);

    //interp test
    CHECK( (NEW(MultExpr)(num3,num2))->interp(Env::empty)->equals(valn6));
    CHECK( (NEW(MultExpr)(num3,num3))->interp(Env::empty)->equals(NEW(NumVal)(9)));
    CHECK( (NEW(MultExpr)(num3,num3copy))->interp(Env::empty)->equals(NEW(NumVal)(9)));
    CHECK( (NEW(MultExpr)(num3,num3))->interp(Env::empty)->equals(num9->interp(Env::empty)));
    CHECK_THROWS_WITH( (NEW(MultExpr)(num3,numX))->interp(Env::empty), "free variable: X" );

    //has_variable test
    CHECK( (NEW(MultExpr)(num3,num3))->has_variable() == false);
    CHECK( (NEW(MultExpr)(num3,numX))->has_variable() == true);
    CHECK( (NEW(MultExpr)(numX,numY))->has_variable() == true);

    //subst test
    CHECK( (NEW(MultExpr)(NEW(Variable)("a"), NEW(NumExpr)(7)))
           ->subst("x", NEW(Variable)("y"))
           ->equals(NEW(MultExpr)(NEW(Variable)("a"), NEW(NumExpr)(7))) == true );
    CHECK( (NEW(MultExpr)(NEW(NumExpr)(9), NEW(NumExpr)(7)))
           ->subst("x", NEW(Variable)("y"))
           ->equals(NEW(MultExpr)(NEW(NumExpr)(9), NEW(NumExpr)(7))) == true );
    CHECK( (NEW(MultExpr)(NEW(Variable)("x"), NEW(Variable)("x")))
           ->subst("x", NEW(Variable)("y"))
           ->equals(NEW(MultExpr)(NEW(Variable)("y"), NEW(Variable)("y"))) == true );

    //toString and pp_to_string
    CHECK(mult3_2->to_string() == "(3*2)");
    CHECK(mult3_2->pp_to_string() == "3 * 2");
    CHECK(mult1a2_3->pp_to_string() == "(1 + 2) * 3");
    CHECK(mult1_2a3->pp_to_string() == "1 * (2 + 3)");
    CHECK(mult3m2_3a2->pp_to_string() == "(3 * 2) * (3 + 2)");


    //Let Tests
    //equals
    CHECK(letx_5->equals(NEW(LetExpr)(NEW(Variable)("X"), NEW(NumExpr)(5), NEW(Variable)("X")))== true);
    CHECK(letx_5->equals(NEW(LetExpr)(NEW(Variable)("X"), NEW(NumExpr)(6), NEW(Variable)("X")))== false);
    //subst
    CHECK(letx_9add5_x->subst("X",NEW(AddExpr)(NEW(Variable)("Y"),NEW(NumExpr)(3)))->equals(letx_9add5_x));

    PTR(LetExpr) let1 = (NEW(LetExpr)(NEW(Variable)("x"),NEW(NumExpr)(1),NEW(AddExpr)(NEW(Variable)("x"), NEW(NumExpr)(2))));

    CHECK( let1->subst("x", NEW(AddExpr)(NEW(Variable)("y"), NEW(NumExpr)(3)))->equals(let1) );
    CHECK( let1->subst("x", NEW(AddExpr)(NEW(Variable)("x"), NEW(NumExpr)(3)))->equals(let1) );
    
    CHECK(Expr::parse_str("(_let x=3 _in  x+15)")->subst("y",numY)->interp(Env::empty)->to_expr()->to_string() == "18");
    CHECK(Expr::parse_str("(_let x=3 _in  x+15)")->has_variable() == true);
    CHECK(Expr::parse_str("(_let x=3 _in  3+15)")->has_variable() == false);

    PTR(LetExpr) let2 = (NEW(LetExpr)(NEW(Variable)("x"),NEW(NumExpr)(1),NEW(AddExpr)(NEW(Variable)("x"), NEW(NumExpr)(2))));

    CHECK( let2->subst("x", NEW(AddExpr)(NEW(Variable)("y"), NEW(NumExpr)(3)))
          ->equals(let2) );

    CHECK(let4->subst("z",NEW(NumExpr)(0))->equals(letz_Add0_2_Addz_32));

    //interp
    CHECK(letx_5->interp(Env::empty)->equals(valn5));
    CHECK(letx_9add5_x->interp(Env::empty)->equals(valn14));
    CHECK(letx_5letx_9add5_x->interp(Env::empty)->equals(valn14));
    CHECK_THROWS_WITH(Expr::parse_str("(_let X=5 _let _in X)"),"input not correct let");
    
    //toString
    CHECK(letx_5->to_string() == "(_let X=5 _in X)");
    CHECK(letx_9add5_x->to_string() == "(_let X=9 _in (5+X))");
    CHECK(letx_5addlety_3addy_2_x->to_string() == "(_let X=5 _in ((_let Y=3 _in (Y+2))+X))");

////test for Parse

    CHECK(Expr::parse_str("(3*2)")->to_string() == "(3*2)");
    CHECK(Expr::parse_str("(_let X=9 _in (5+X))")->to_string() == "(_let X=9 _in (5+X))");
    CHECK(Expr::parse_str("(_let X=5 _in ((_let Y=3 _in (Y+2))+X))")->to_string() == "(_let X=5 _in ((_let Y=3 _in (Y+2))+X))");
    CHECK(Expr::parse_str("(_let X=5 _in X)")->to_string() == "(_let X=5 _in X)");
    
    CHECK(Expr::parse_str("(true)")->to_string() == "true");
    CHECK(Expr::parse_str("(false)")->to_string() == "false");
    CHECK(Expr::parse_str("(_if _true _then 3 _else 4)")->interp(Env::empty)->to_expr()->to_string() == "3");
    CHECK(Expr::parse_str("(_let f = _fun (x) x + 1_in  f(10))")->interp(Env::empty)->to_expr()->to_string() == "11");
    
    CHECK_THROWS_WITH(Expr::parse_str("(_let f = _fmun (x) x + 1_in  f(10))")->interp(Env::empty),"input not correct");
    
    CHECK_THROWS_WITH(Expr::parse_str("(_let f = _fun (x x + 1_in  f(10))")->interp(Env::empty),"input not correct");
    
    CHECK_THROWS_WITH(Expr::parse_str("(_if _true _tlhen 3 _else 4)")->interp(Env::empty),"input not correct");
    
    CHECK_THROWS_WITH(Expr::parse_str("(_if 3=3 _tlhen 3 _else 4)")->interp(Env::empty),"= charater not used correctly");

    CHECK(Expr::parse_str("(_if _false _then 3 _else 4)")->interp(Env::empty)->to_expr()->to_string() == "4");
    
    CHECK_THROWS_WITH(Expr::parse_str("(_ilet X=5 _in X)")->to_string(), "input not correct");
    
    CHECK_THROWS_WITH(Expr::parse_str("(_klet X=5 _in X)")->to_string(), "input not correct for let");
    CHECK(Expr::parse_str("(-3*2)")->to_string() == "(-3*2)");
    CHECK_THROWS_WITH(Expr::parse_str("(-3*2")->to_string(), "Missing close parenthesis");
    CHECK_THROWS_WITH(Expr::parse_str("(_llet X=9 _in (5+X))")->to_string(), "consume mismatch");
    CHECK_THROWS_WITH(Expr::parse_str("($let X=9 in (5+X))")->to_string(), "invalid input");
    
    
// interp by step testing
    CHECK(Step::interp_by_steps(Expr::parse_str("_let countdown = _fun(countdown)_fun(n) _if n == 0 _then 0_else countdown(countdown)(n + -1) _in countdown(countdown)(1000000)"))->to_expr()->to_string() == "0");
    CHECK(Step::interp_by_steps(Expr::parse_str("(3*2)"))->to_expr()->to_string() == "6");
    CHECK(Step::interp_by_steps(Expr::parse_str("(3+2)"))->to_expr()->to_string() == "5");
    CHECK(Step::interp_by_steps(Expr::parse_str("(_let X=9 _in (5+X))"))->to_expr()->to_string() == "14");
    CHECK(Step::interp_by_steps(Expr::parse_str("_if 3==3 _then 8 _else 9"))->to_expr()->to_string() == "8");
    CHECK(Step::interp_by_steps(Expr::parse_str("_if 4==3 _then 8 _else 9"))->to_expr()->to_string() == "9");
    CHECK(Step::interp_by_steps(Expr::parse_str("4==4"))->to_expr()->to_string() == "_true");
    CHECK(Step::interp_by_steps(Expr::parse_str("_let f = _fun (x) x*6 _in f(2)"))->to_expr()->to_string() == "12");

    
    CHECK_THROWS_WITH(Expr::parse_str("1000000000000000000000000000"),"Int OverFlow" );
    



};
