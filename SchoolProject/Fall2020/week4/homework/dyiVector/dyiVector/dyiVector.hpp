//
//  dyiVector.hpp
//  dyiVector
//
//  Created by Garret Wasden on 9/15/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#ifndef dyiVector_hpp
#define dyiVector_hpp

#include <stdio.h>
using namespace std;

template <class T>
class myVector {
    private:
        T * data;
        int capacity;
        int size;
    
    public:
    
//      rule of 3
    myVector(const myVector& rhs){

        data = new T [capacity + 1];
        for (int i = 1; i< capacity + 1; i++){
            data[i] = rhs.data[i];
        }
    }

    myVector& operator=(const myVector& rhs){
        capacity = rhs.capacity;
        T* newData = new T [capacity + 1];
        for (int i = 1; i< capacity; i++){
            newData[i] = rhs.data[i];
        }
        delete [] data;
        data = newData;
        return *this;
    }

    ~myVector(){
        delete [] data;
    }
    
    myVector(int initialCapacity){
           capacity = initialCapacity;
           size = 0;
           data = new T [initialCapacity];
       };
    
    T operator[](int position)const{
        return data[position];
    }
    
    T& operator[](int position){
        return data[position];
    }
    
    void growVector(){
       capacity = (capacity * 2);
        T * newArray = new T [capacity];
        for(int i = 0; i < size; i++){
            newArray[i] = data[i];
        }
        delete [] data;
        data = newArray;
        newArray = nullptr;
    }
    
    void freeVector(){
        delete data;
        data = nullptr;
    }
    
    void pushBack(T value){
        if ( size + 1 > capacity){
            growVector();
        }
        T spot = size;
       data[spot] = value;
       size++;
    }
    
    void popBack(){
        size--;
    }
    
    T get(int index){
        return data[index];
    }
    
    void set(int index, T newValue){
       data[index] = newValue;
    }
    
    int getSize(){
        return size;
    }
    int getCapacity(){
        return capacity;
    }
    
    
    bool operator== (const myVector& rhs){
//get smaller of the sizes from lhs or rhs;
        int length = ((size < rhs.size) ? size:rhs.size);
        T testing = data[1];
        T test = rhs.data[1];
        for (int i = 1 ; i < length; i++){
            testing = data[i];
             test = rhs.data[i];
            if ( data[i] !=  rhs.data[i]){
                return false;
            }
        }
        return true;
    }
    
    bool operator!= (const myVector& rhs){
        return !(*this == rhs);
    }
    
    bool operator>= ( myVector& rhs){
//get smaller of the sizes from lhs or rhs;
        int length = ((size < rhs.size) ? size:rhs.size);
        int one;
        int two;
        for (int i = 0; i < length; i++){
            two = rhs.data[i];
            one = data[i];
            if (rhs.data[i] > data[i]){
                return false;
            }
        }
        return true;
    }
    
    bool operator<= (myVector& rhs){
        return !(rhs < *this);
    }
    
    bool operator< (myVector& rhs){
        return !(*this >= rhs);
    }
    bool operator> (myVector& rhs){
        return !(*this <= rhs);
    }
    
// adding stuff to make it work with the standard libray;
    
    T* begin(){
        return data;
    }
    
    T* end(){
        return data + size;
    }
    
    T* begin()const{
        return data;
    }
    
    T* end()const{
        return data + size;
    }
    
};

#endif /* dyiVector_hpp */
