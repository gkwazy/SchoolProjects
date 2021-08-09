//
//  MemoryMakerHelper.cpp
//  mallocReplacement
//
//  Created by Garret Wasden on 3/22/21.
//

#include "MemoryMakerHelper.hpp"
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

MemoryMakerHelper::MemoryMakerHelper(){
    size = getpagesize();
};

MemoryMakerHelper::~MemoryMakerHelper(){
    
};

HashTable MemoryMakerHelper::getTable(){
    return table;
};

void* MemoryMakerHelper::allocate(size_t bytes){
    void* ptr = mmap(NULL, bytes, PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANONYMOUS|MAP_PRIVATE,0,0);
    if (ptr == MAP_FAILED){
        perror("mmap failed in allocate");
        _exit(1);
    }
    table.insert(ptr, bytes);
    return ptr;
};

void MemoryMakerHelper::deallocate(void* ptr){
    if (munmap(ptr, table.get(ptr))!= 0){
        perror("mumap failed");
        _exit(1);
    }
};

