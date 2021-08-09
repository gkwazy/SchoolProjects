//
//  main.cpp
//  ThreadSafe
//
//  Created by Garret Wasden on 4/19/21.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "ConcurrentQueueTest.hpp"
  
int main(int argc, char** argv)
{
    int produce = atoi(argv[1]);
    int consumer = atoi(argv[2]);
    int number = atoi(argv[3]);

//    ConcurrentQueueTest tests;
    
    bool testing = testQueue(produce,consumer,number);
    if(testing){
        std::cout << "winner\n";
    }else{
        std::cout << "wrong\n";
    }
    
    return 0;
}
