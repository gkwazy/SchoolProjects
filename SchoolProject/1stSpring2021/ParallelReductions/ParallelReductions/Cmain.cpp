////
////  Cmain.cpp
////  ParallelReductions
////
////  Created by Garret Wasden on 4/26/21.
////
//
//#include "Cmain.hpp"
//#include <iostream>
//#include <vector>
//#include <thread>
//#include <mutex>
//
//
//
//template<typename T>
//void addThreadParts(int numI, T a[], std::vector<T> &sums, int arraySize, size_t num_threads){
//    T tempSum = 0;
//    for(int i = numI; i < arraySize; i = i+(int)num_threads){
//        tempSum = a[i] + tempSum;
//    }
//    sums.push_back(tempSum);
//}
//
//template<typename T>
//auto parallel_sum_std(T a[], size_t num_threads){
//    std::vector<std::thread> threads;
//    std::vector<T> sums;
//    sums.reserve(num_threads);
//    threads.reserve(num_threads);
//    int arraySize = sizeof(a);
//    for(int i = 0; i < sizeof(num_threads); i++){
//        threads.push_back(std::thread(&addThreadParts(i, a,sums,arraySize,num_threads)));
//    }
//    for (std::thread & th : threads)
//        {
//            if (th.joinable())
//                th.join();
//        }
//    for(int i = 0; i < sizeof(sums);i++){
//        std::cout << sums[i];
//    }
//    return 1;
//}
//
