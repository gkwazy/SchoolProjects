INCS = cmdline/cmdline.hpp Expr/Expr.hpp Val/Val.hpp Test/Test.hpp Env/Env.hpp Step/Step.hpp Cont/Cont.hpp
OBJS = main.o cmdline/cmdline.o Expr/Expr.o Val/Val.o Test/Test.o Env/Env.o Step/Step.o Cont/Cont.o 
TESTINCS = testGenerator/testGen.hpp
TESTOBJS = testGenerator/testMain.o testGenerator/testGen.o testGenerator/exec.o
CXXFLAGS = --std=c++14 -O2 
 
msdscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS)

test_msdscript: $(TESTOBJS)
	$(CXX) $(CXXFLAGS) -o test_msdscript $(TESTOBJS)

.PHONY: test
test:msdscript
	./msdscript --test                          
main.o: main.cpp $(INCS)
 
cmdline.o: cmdline.cpp $(INCS)

Expr.o: Expr/Expr.cpp $(INCS)

Val.o: Val/Val.cpp $(INCS)

Test.o: Test/Test.cpp $(INCS)

Env.o: Env/Env.cpp $(INCS)

Step.o: Step/Step.cpp $(INCS)

Cont.o: Cont/Cont.cpp $(INCS)

testMain.o: testGenerator/testMain.cpp $(TESTINCS)

testGen.o: testGenerator/testGen.cpp $(TESTINCS)

exec.o: testGenerator/exec.cpp $(TESTINCS)
