# MSD6015
Overview
    MSDScript is a system program for interpreting expressions and returning and value for the expression. MSDScript can evaluate simple Functions, Let statements, arithmetic (Add, Multiply), and Booleans. 

How to install/build
If wanting to use MSDScript just like a library download and place both the cmdline.hpp and libmsdscript.a  into your home directory. Inside of your application place, “#include cmdline.hpp” will connect your application with the library. To use the library use the function runCommand(std::string command, std::string input); the command filed is how you want the command to run based on the different modes as seen below. The input command is the string you wise to have interpreted. The runCommand() will return a std::string;
    To build the application there is a Make file that is in the zip file. In the main directory of MSDScript in the terminal typing “make” will make an executable named   “msdscript” from there you can use the commands from below to run the application. If you are wanting to run the application as a library you will need to make a copy of the cmdline.hpp file from the zip and place it in your main directory. From there in the main directory of the MSDScript file run the command  “ar -ruv libmsdscript.a Expr/Expr.o Val/Val.o Cont/Cont.o Evn/Evn.o Step/Step.o cmdline/cmdline.o”. Place the libmsdscript.a that is made in the same location as the copy of cmdline.hpp in you main directory.  



you can run Mode
    MSDScript can be run in different modes
“--interp” - this mode will run through the provided expression and return a value or simplified function. This mode uses the C++ stack and will run out of stack memory if the expression is too large. 
“--step” this mode will run the interpret the function but avoid using the C++ stack and interpret the expression as it reads it.
“--print” This mode will interpret the given expression and return what was interpreted as a string. 

How it works under the hood. 
MSDScript parses text into expressions from there it will solve the expressions. MSDScript evaluates everything down to expressions. There are several different types of expression that MSDScript will use. MSDScript will also prioritize different types of expressions over others( for example in the expression “4+3*8” “3*8” will be calculated before “4+3”) Here is a  layout of the expression hierarchy with the highest being at the bottom.
<expr> = <number>
|<boolean>
| <expr> == <expr>
|<expr> + <expr>
|<expr>*<expr>
|<expr>(<expr>)
|<variable>
|_let <variable> = <expr> _in <expr>
|_if <expr> _then <expr> _else <expr>
|_fun( <expr> ) <expr>

Here are a definition and how to use the expressions

<number>: this expression will be using regular integers(1,2,3…) MSDScript will return the number because this is the base and a number can not be evaluated further. Numbers can also have “-” placed in front of them to represent negatives numbers. 

<boolean>: this will return a true or false. The user can enter ”_true” or “_fasle” for the values. MSDScript and evaluate booleans as well. If two expressions are entered with an “==” between then MSDScript will return a true or false. For example -”3==4” is false, “(4+3)==7” is true, “_let x = 3 _in x==3” is true; boolean will be evaluated after “+” but before “<number>s

<variable>: variables expressions are used in another expression to represent expressions. Variables and be a single letter “x” or a string “xIsTheBest”. When interpreting a variable if there is no value assigned to the variable then the application will return the letter or string of the variable.  Variables can be assigned in “_lets” and “_fun”; “_let x = 3 _in x” will set the variable x to equal 3. “_let x = 3 _in _if x==4 _then 5 _else x” will return 3 because “x==4” will be interpreted as “3==4” or “_false” so the _else will be picked and return “x” or 3. “_let myVar _in _fun(myVar) myVar+9 _in f(8)” will interpret as 17 because “myVar” will be set to 8 from the _fun expression. 

<expr> ==<expr>: is use to compare expressions and return a true or false. This is used in “_if” to decided if the “_then” or “_else” is returned. 

<expr>+<expr>: expression can be added together. “3+4” will return 7. “x+3” will return “x+3” because that is as far as it can be evaluated. “_let x = 3 _in x+3” will return 6. “+” will be evaluated after ”*” but before”<booleans>

<expr>*<expr> : expressions can be Multiplied together. “3*3” returns 9. “x*3” will return “x*3” because that is as far as it can be evaluated. “_let x = 3 _in x*3” will return 9. “+” will be evaluated after ”( )” but before ”+”.

_let <variable> = <expr> _in <expr>: let expressions must follow this format or the word “_let” followed by a variable type expression (“x”,”g”,”y”,....) with the symbol ”=” followed by an expression. This will assign the <variable> with the value of the <expr>. For example “_let c=4” _in c” c has the value of 4. Or “_let myFun =( _if 3==4 _then 4 _else 5) _in myFun”  then “myFun” will have the value of 5 because 3==4 is false. The word “_in” must then be used followed by the last expression. Examples “ “_let x = 3 _in x” will return 3.  “_let x = 3*3 _in x” will return 9  “_let x = 3*3 _in x+4” will return 13.


_if <expr> _then <expr> _else <expr>: if expressions are in the follow format. “_if “ must be first and be a condition that the expression is checking. The <expr> after _if can any expression. If the exposition is just a value that will return as true. If the expression is a “==” then it will return the base of the values. If the expression is true the if expression will return the _then <expr> or the expression place after the “_then” if the statement is false then it will return the “_else” expression

_fun(<expr>)<expr>: the _fun expression is for functions. _fun expressions are considered just expression and must be paired with other exprs for work to be completed. _fun (x) x+1 when parse is still _fun(x) x+1 to use functions pair _fun with _let. After words you can call the function with (<expr>)<expr> for example “_let f = _fun(x) x+1 _in f(10) this will return 11. _fun expression are <expr> and as such can be used like other expressions. For example “_let f = _fun(x) x+1 _in f(10)+ f(20)” this will return 32 because “f(10)” is an expression that returns 11 and “f(20)” returns 21 and is also an expression. After they are interpreted we are left with <expr> + <expr> or 32 in this case. 

<expr>(<expr>): performs like the “_fun” command and is uses to make functions. After setting a fun (for example _let f = _fun(x) x+1 _in f(10)) “f(10)” will be a function call with f(10) being interpreted as 10+1.




Report bugs and errors 
Report Bugs to https://github.com/gkwazy/MSD6015/issues with the input on what you were trying to parse and the error code. 
