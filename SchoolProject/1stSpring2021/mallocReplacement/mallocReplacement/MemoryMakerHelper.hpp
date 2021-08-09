//
//  MemoryMakerHelper.hpp
//  mallocReplacement
//
//  Created by Garret Wasden on 3/22/21.
//

#ifndef MemoryMakerHelper_hpp
#define MemoryMakerHelper_hpp

#include <stdio.h>
#include "HashTable.hpp"

class MemoryMakerHelper{
public:
    MemoryMakerHelper();
    ~MemoryMakerHelper();
    
    void* allocate(size_t bytesToAllocate);
    void deallocate(void* ptr);
    HashTable getTable();
    
private:
    HashTable table;
    size_t size;
    

};

#endif /* MemoryMakerHelper_hpp */
