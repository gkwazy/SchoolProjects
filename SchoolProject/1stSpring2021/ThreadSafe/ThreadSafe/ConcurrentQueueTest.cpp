//
//  ConcurrentQueueTest.cpp
//  ThreadSafe
//
//  Created by Garret Wasden on 4/19/21.
//

//#include "ConcurrentQueueTest.hpp"
#include "SerialQueue.hpp"
#include "ConcurrentQueue.hpp"
#include <iostream>
#include <vector>
#include <thread>


//ConcurrentQueueTest::ConcurrentQueueTest(){
//
//}
//
//void testEnqueue(int number){
//    for(int i = 0; i < number; i++){
//        myqueue.enqueue(number);
//    }
//}
//void ConcurrentQueueTest::testDequeue(int number){
//    int temp;
//    for(int i = 0; i < number; i++){
//        myqueue.dequeue(&temp);
//    }
//}
//
void here(int one){
    std::cout<< one;
}

bool testQueue(int num_producers, int num_consumers, int num_ints){
    std::cout << "You have entered " << num_producers
         << " producers:" << "\n";
    std::cout << "You have entered " << num_consumers
         << " consumers:" << "\n";
    std::cout << "You have entered " << num_ints
         << " nums:" << "\n";
    int temp;
    std::vector<std::thread> threads;
    threads.reserve(num_producers+num_consumers);
    static ConcurrentQueue<int> myqueue;
    
    
    for (int i = 0; i< num_producers; i++){
        threads.push_back(std::thread(&ConcurrentQueue<int>::enqueueTest,&myqueue,num_ints,num_ints));
    };
    for (int i = 0; i<num_consumers; i++){
        threads.push_back(std::thread(&ConcurrentQueue<int>::dequeueTest,&myqueue,&temp,num_ints));
    };
    
    for (std::thread & th : threads)
        {
            if (th.joinable())
                std::cout << "5\n";
                th.join();
        }
    
    
    
    return (myqueue.size_ == (num_producers - num_consumers)*num_ints);
};
