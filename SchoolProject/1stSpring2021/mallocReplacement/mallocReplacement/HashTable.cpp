//
//  HashTable.cpp
//  mallocReplacement
//
//  Created by Garret Wasden on 3/22/21.
//
#include <sys/mman.h>
#include <unistd.h>
#include "HashTable.hpp"

HashTable::HashTable(){
    cap = getpagesize() / sizeof(TableEntry);
    size = 0;
    table = (TableEntry*) mmap(NULL, cap * sizeof(TableEntry), PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
    if (table == MAP_FAILED){
        perror("mmap failed in constructor");
        _exit(1);
    }
}

HashTable::~HashTable(){
    
}

size_t HashTable::getSize(){
    return size;
}

int HashTable::makeHash(void* ptr){
    int hash = (int)((size_t)ptr >> 12) % cap;
    return hash;
}

size_t HashTable::get(void* ptr){
    size_t myHash = makeHash(ptr);
    while(table[myHash].ptr != ptr && table[myHash].flag == 1){
        myHash++;
        if (myHash >= cap){
            myHash -= cap;
        }
    }
    if (table[myHash].flag == 1){
        return table[myHash].size;
    }
    return -1;
}

void HashTable::insert(void* ptr, size_t insertSize){
    float nearingCap = size/cap;
    if (nearingCap > 0.6){
        grow();
    }
    size_t myHash = makeHash(ptr);
    
    while(table[myHash].flag == 1){
        myHash++;
        if (myHash >= cap){
            myHash -= cap;
        }
    }
    
    table[myHash].ptr = ptr;
    table[myHash].size = insertSize;
    table[myHash].flag = 1;
    size++;
}

void HashTable::grow(){
    size_t biggerCap = cap * 2;
    TableEntry* biggerTable = (TableEntry*) mmap(NULL, biggerCap * sizeof(TableEntry), PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANONYMOUS|MAP_PRIVATE,0,0);
    if(biggerTable == MAP_FAILED){
        perror("mmap failed in grow");
        _exit(1);
    }
    TableEntry* tempTable = table;
    size_t tempCap = cap;
    this->cap = biggerCap;
    this->table = biggerTable;
    this->size = 0;
    for ( int i = 0; i < tempCap; i++){
        if(tempTable[i].flag == 1){
            insert(tempTable[i].ptr, tempTable[i].size);
        }
    }
}

void HashTable::remove(void* ptr){
    size_t myHash = makeHash(ptr);
    while(table[myHash].ptr != ptr){
        myHash++;
        if(myHash >= cap){
            myHash -= cap;
        }
    }
    if ( table[myHash].flag == 1){
        table[myHash].flag = -1;
        size--;
    }
}




