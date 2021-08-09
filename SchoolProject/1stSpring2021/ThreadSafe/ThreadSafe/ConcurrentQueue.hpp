#pragma once
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

template <typename T>
class ConcurrentQueue{
private:
  struct Node{
    T data;
    Node* next;
  };

    Node* head;
    Node* tail;
   
    std::mutex m;
    std::condition_variable cv;
    bool headWork = false;

    
public:
    int size_;
    ConcurrentQueue()
    :head(new Node{T{}, nullptr}), size_(0)
  {
    tail = head;
  }

  void enqueue(const T& x){
      Node* temp = new Node{x,nullptr};
      std::unique_lock<std::mutex> my_lock(m);
//      while (headWork == true){
//          cv.wait();
//      }
      if (head == nullptr){
          head = new Node{T{}, nullptr};
      }
      if ( head->next == nullptr && size_ < 1){
          head = temp;
          tail = head;
      }else{
          tail->next = temp;
          tail = temp;
      }
      size_++;
      cv.notify_all();
  }

  bool dequeue(T* ret){
      std::unique_lock<std::mutex> my_lock(m);
     while(size_ == 0){
          cv.wait(my_lock);
      }
      if (head == nullptr){
          return false;
      }else if(head->next == nullptr){
          ret = &head->data;
          delete head;
          head = nullptr;
          size_--;
      }else{
          Node* temp = head->next;
          ret = &head->data;
          delete head;
          head = temp;
          size_--;
      }
      cv.notify_all();
      return true;
  }

  ~ConcurrentQueue(){

    while(head){
      Node* temp = head->next;
      delete head;
      head = temp;
    }
  }

  int size() const{ return size_;}
    
    
    void enqueueTest(const T& x,int num){
        for(int i = 0; i < num; i++){
            enqueue(x);
        }
        std::cout << "pro done\n";
    }
    void dequeueTest(T* ret, int num){
        for(int i = 0; i < num; i++){
            dequeue(ret);
        }
        std::cout << "con done\n";
    }
    
};

