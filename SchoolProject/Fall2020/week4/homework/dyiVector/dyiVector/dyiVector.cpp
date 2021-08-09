//
//  dyiVector.cpp
//  dyiVector
//
//  Created by Garret Wasden on 9/15/20.
//  Copyright © 2020 Garret Wasden. All rights reserved.
//

#include "dyiVector.hpp"



//myVector::myVector(int initialCapacity){
//    data = new int[initialCapacity];
//    capacity = initialCapacity;
//    size = 0;
//}
//
//myVector::myVector(const myVector& rhs){
//    
//    data = new int[capacity + 1];
//    for (int i = 1; i< capacity + 1; i++){
//        data[i] = rhs.data[i];
//    }
//}
//
//myVector& myVector::operator=(const myVector& rhs){
//    capacity = rhs.capacity;
//    int* newData = new int[capacity + 1];
//    for (int i = 1; i< capacity + 1; i++){
//        newData[i] = rhs.data[i];
//    }
//    delete [] data;
//    data = newData;
//    return *this;
//}
//
//myVector::~myVector(){
//    delete [] data;
//}
//
//int myVector::operator[](int position)const{
//    return data[position];
//}
//
//int& myVector::operator[](int position){
//    return data[position];
//}
//
//void myVector::growVector(){
//   capacity = (capacity * 2);
//    int * newArray = new int[capacity];
//    for(int i = 0; i < size; i++){
//        newArray[i] = data[i];
//    }
//    delete [] data;
//    data = newArray;
//    newArray = nullptr;
//}
//
//void myVector::freeVector(){
//    delete data;
//    data = nullptr;
//}
//
//void myVector::pushBack(int number){
//    if ( size + 1 > capacity){
//        growVector();
//    }
//    int spot = size;
//   data[spot] = number;
//   size++;
//}
//
//void myVector::popBack(){
//    size--;
//}
//
//int myVector::get(int index){
//    return data[index];
//}
//
//void myVector::set(int index, int newValue){
//   data[index] = newValue;
//}
//
//int myVector::getSize(){
//    return size;
//}
//int myVector::getCapacity(){
//    return capacity;
//}
