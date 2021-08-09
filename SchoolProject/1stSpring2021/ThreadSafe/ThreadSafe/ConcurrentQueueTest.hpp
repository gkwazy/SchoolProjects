//
//  ConcurrentQueueTest.hpp
//  ThreadSafe
//
//  Created by Garret Wasden on 4/19/21.
//

#ifndef ConcurrentQueueTest_hpp
#define ConcurrentQueueTest_hpp

#include <stdio.h>
#include "ConcurrentQueue.hpp"

//class ConcurrentQueueTest{
//public:
//ConcurrentQueue<int> myqueue;
//
//ConcurrentQueueTest();
bool testQueue(int num_producers, int num_consumers, int num_ints);
//void testEnqueue(int number);
//void testDequeue(int number);
//};

#endif /* ConcurrentQueueTest_hpp */
