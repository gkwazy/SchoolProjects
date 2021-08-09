//
//  main.cpp
//  mallocReplacement
//
//  Created by Garret Wasden on 3/22/21.
//

#include <iostream>
#include "MemoryMakerHelper.hpp"
#include "HashTable.hpp"
#include <vector>
#include <chrono>

int main(int argc, const char * argv[]) {
    MemoryMakerHelper slowMalloc;
    std::vector<int> tempVec;
    for(int i = 0; i< 50000; i++){
        tempVec.push_back(rand() % 50000 + 1);
    }
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> myAll, myDeAll, Mall, DeMall;
    std::vector<void*> theAllocator;
    
    start = std::chrono::system_clock::now();
    for(int i = 0; i< 50000; i++){
        void* ptr = slowMalloc.allocate(tempVec[i]);
        theAllocator.push_back(ptr);
    }
    end = std::chrono::system_clock::now();
    myAll = end - start;
    
    start = std::chrono::system_clock::now();
    for(int i = 0; i< 50000; i++){
       slowMalloc.deallocate(theAllocator[i]);
    }
    end = std::chrono::system_clock::now();
    myDeAll = end - start;
    
    std::vector<void*> fastAllocator;
    start = std::chrono::system_clock::now();
    for(int i = 0; i< 50000; i++){
        void* ptr = malloc(tempVec[i]);
        fastAllocator.push_back(ptr);
    }
    end = std::chrono::system_clock::now();
    Mall = end - start;
    
    start = std::chrono::system_clock::now();
    for(int i = 0; i< 50000; i++){
       free(fastAllocator[i]);
    }
    end = std::chrono::system_clock::now();
    DeMall = end - start;
    
    std::cout << "Total time to run my malloc: " << myAll.count() << std::endl;
    std::cout << "Total time to run true malloc: " << Mall.count() << std::endl;
    std::cout << "Total time to run my free: " << myDeAll.count() << std::endl;
    std::cout << "Total time to run true free: " << DeMall.count() << std::endl;
    
    return 0;
}
