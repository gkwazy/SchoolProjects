//
//  main.cpp
//  assemblyPro
//
//  Created by Garret Wasden on 2/7/21.
//

#include <cstdio>
#include <iostream>
#include <sys/time.h>
#include <cstdlib>

extern "C" {

void sayHello();
void myPuts(const char* c, int len);
timeval myGTOD();

}



int main(int argc, const char * argv[]) {
    timeval current_time = myGTOD();
    std::cout << current_time.tv_sec;
    printf("seconds : %ld\nmicro seconds : %d\n",
        current_time.tv_sec, current_time.tv_usec);
    
    gettimeofday(&current_time, NULL);
    printf("seconds : %ld\nmicro seconds : %d\n",
        current_time.tv_sec, current_time.tv_usec);
    sayHello();
    myPuts("hi\n",4);
    
    
    
    
    return 0;
}
