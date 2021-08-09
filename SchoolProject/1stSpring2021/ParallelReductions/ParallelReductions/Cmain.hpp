//
//  Cmain.hpp
//  ParallelReductions
//
//  Created by Garret Wasden on 4/26/21.
//

#ifndef Cmain_hpp
#define Cmain_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

template<typename T>

class Cmain{
public:
    std::vector<T> sums;
    std::vector<std::thread> threads;
    size_t arraySize;
    size_t numOfThreads;
    T trueValue;
    std::mutex m;
    std::condition_variable cv;
    bool updating = false;
    int runTimes;
    
    void addThreadParts(int numI, T a[]){
        T tempSum = 0;
        for(int i = numI; i < arraySize; i = i+(int)numOfThreads){
            tempSum = a[i] + tempSum;
        }
        std::unique_lock<std::mutex> my_lock(m);
        
        while( updating == true){
            cv.wait(my_lock);
        }
        
        updating = true;
        sums.push_back(tempSum);
        updating = false;
    }
    
    auto findTrueValue(T a[]){
        T temp = 0;
        for(int i = 0; i < arraySize; i++){
            temp = a[i] + temp;
        }
        return temp;
    }

    auto parallel_sum_std(T a[],size_t N, size_t num_threads){
        //Set up the variables for the test
        runTimes = 5000;
        std::vector<double> time;
        time.reserve(runTimes);
        numOfThreads = num_threads;
        sums.reserve(num_threads);
        threads.reserve(num_threads);
        arraySize = N;
        trueValue = findTrueValue(a);
        
        //zero out the array so it starts the same every time
        for(int i = 1; i < sums.size(); i++){
            sums[i] = 0;
        }
        
        // repeat the test "runTimes" number of times
        for(int j = 0; j < runTimes; j++){
            auto start = std::chrono::steady_clock::now();
            
            for(int i = 0; i < num_threads; i++){
                threads.push_back(std::thread(&Cmain::addThreadParts,this,i,a));
            }
            
            for (std::thread & th : threads)
                {
                    if (th.joinable())
                        th.join();
                }
            
            for(int i = 1; i < sums.size(); i++){
                sums[0] = sums[0] + sums[i];
            }
            auto end = std::chrono::steady_clock::now();
            time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            if(sums[0]!=trueValue){
                throw std::runtime_error("incorrect value");
            }
            threads.clear();
            threads.reserve(num_threads);
            for(int i = 0; i < sums.size(); i++){
                sums[i] = 0;
            }
        }
        
        for(int i = 1; i< time.size(); i++){
            time[0] = time[0]+ time[i];
        }
        time[0] = time[0]/time.size();
        
        return time[0];
    }
    
};


#include "/usr/local/opt/libomp/include/omp.h"
template<typename T>
class OpenMPC{
public:
    std::vector<std::thread> threads;
    size_t arraySize;
    size_t numOfThreads;
    T trueValue;
    std::mutex m;
    std::condition_variable cv;
    bool updating = false;
    int runTimes;
    
    auto findTrueValue(T a[]){
        T temp = 0;
        for(int i = 0; i < arraySize; i++){
            temp = a[i] + temp;
        }
        return temp;
    }
    auto parallel_sum_std(T a[],size_t N, size_t num_threads){
        omp_set_num_threads(num_threads);
        
        //Set up the variables for the test
        runTimes = 5000;
        std::vector<double> time;
        time.reserve(runTimes);
       
        arraySize = N;
        trueValue = findTrueValue(a);
        int calVal = 0;
        // repeat the test "runTimes" number of times
        int id = 0;
        int nthrds = 0;
        for(int j = 0; j < runTimes; j++){
            calVal = 0;
            auto start = std::chrono::steady_clock::now();
            
            #pragma omp parallel
            {
                T tempSum = 0;
                id = omp_get_thread_num();
                nthrds = omp_get_num_threads();
                for(int i = omp_get_thread_num(); i < arraySize; i = i+(int)num_threads){
                    tempSum = tempSum + a[i];
                }
            #pragma omp critical
                {
                calVal +=tempSum;
                }
            }
            auto end = std::chrono::steady_clock::now();
            time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            
            if(calVal!=trueValue){
                throw std::runtime_error("incorrect value");
            }
        }

        for(int i = 1; i< time.size(); i++){
            time[0] = time[0]+ time[i];
        }
        time[0] = time[0]/time.size();

        return time[0];
    }
};

template<typename T>
class reduOpenMPC{
public:
    std::vector<std::thread> threads;
    size_t arraySize;
    size_t numOfThreads;
    T trueValue;
    std::mutex m;
    std::condition_variable cv;
    bool updating = false;
    int runTimes;
    
    auto findTrueValue(T a[]){
        T temp = 0;
        for(int i = 0; i < arraySize; i++){
            temp = a[i] + temp;
        }
        return temp;
    }
    auto parallel_sum_std(T a[],size_t N, size_t num_threads){
        omp_set_num_threads(num_threads);
        
        //Set up the variables for the test
        runTimes = 5000;
        std::vector<double> time;
        time.reserve(runTimes);
       
        arraySize = N;
        trueValue = findTrueValue(a);
        T calVal = 0;
        // repeat the test "runTimes" number of times
        for(int j = 0; j < runTimes; j++){
            calVal = 0;
            auto start = std::chrono::steady_clock::now();
            
            #pragma omp parallel for reduction(+:calVal)
            {
                for(int i = 0; i < arraySize; i++){
                    calVal += a[i];
                }
            }
            auto end = std::chrono::steady_clock::now();
            time.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            
            if(calVal!=trueValue){
                throw std::runtime_error("incorrect value");
            }
        }

        for(int i = 1; i< time.size(); i++){
            time[0] = time[0]+ time[i];
        }
        time[0] = time[0]/time.size();

        return time[0];
    }
};



#endif /* Cmain_hpp */
