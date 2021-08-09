//
//  HashTable.hpp
//  mallocReplacement
//
//  Created by Garret Wasden on 3/22/21.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <stdio.h>


struct TableEntry{
    void* ptr;
    size_t size;
    size_t flag;
};

class HashTable{
public:
    HashTable();
    ~HashTable();
    size_t getSize();
    
    void insert(void* table,size_t size);
    void remove(void* table);
    size_t get(void* table);
    
    
private:
    TableEntry* table;
    size_t cap;
    size_t size;
    int makeHash(void* ptr);
    void grow();
};







#endif /* HashTable_hpp */
