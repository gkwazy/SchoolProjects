//
//  SerialQueueTests.cpp
//  ThreadSafe
//
//  Created by Garret Wasden on 4/15/21.
//

#include <stdio.h>
#include <iostream>
#include "SerialQueue.hpp"
#include "ConcurrentQueue.hpp"

int __main(int argc, const char * argv[]) {
    ConcurrentQueue<int> linkList;
    linkList.enqueue(4);
    linkList.enqueue(6);
    int *temp = nullptr;
    
    if (linkList.size() != 2){
        throw std::runtime_error("size incorrect after enqueue twice");
    }
    
    linkList.dequeue(temp);
    if(*temp != 4){
        throw std::runtime_error("first dequeue failed");
    }
    linkList.dequeue(temp);
    if(*temp != 6){
        throw std::runtime_error("second dequeue failed");
    }
    if (linkList.size() != 0){
        throw std::runtime_error("size incorrect after dequeue twice");
    }
    return 0;
}
