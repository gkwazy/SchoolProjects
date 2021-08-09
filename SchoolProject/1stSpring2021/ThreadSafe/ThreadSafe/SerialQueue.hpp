#pragma once

template <typename T>
class SerialQueue{
private:
  struct Node{
	T data;
	Node* next;
  };

  Node* head;
  Node* tail;
  int size_;

public:
  SerialQueue()
	:head(new Node{T{}, nullptr}), size_(0)
  {
	tail = head;
  }


  void enqueue(const T& x){
      Node* temp = new Node{x,nullptr};
      if ( head->next == nullptr && size_ < 1){
          head = temp;
          tail = head;
      }else{
          tail->next = temp;
          tail = temp;
      }
      size_++;
  }

  bool dequeue(T* &ret){
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
      return true;
  }

  ~SerialQueue(){

	while(head){
	  Node* temp = head->next;
	  delete head;
	  head = temp;
	}
  }

  int size() const{ return size_;}  
};
