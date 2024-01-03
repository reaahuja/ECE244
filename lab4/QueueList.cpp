#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer* customer) { head = customer; }

QueueList::~QueueList() {
  // Customer* current = head; 
  // if (current->get_next() == nullptr){
  //   delete current;
  // }else{
  //   while(current!= nullptr){
  //     Customer* temp = current;
  //     current = current->get_next();
  //     delete temp;
  //   }
  // }

  delete head;
}

Customer* QueueList::get_head() { return head; }

void QueueList::enqueue(Customer* customer) {
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head
  Customer* current = head; 
  if (head == nullptr){
    head = customer;
    customer->set_next(nullptr);
  }else{
    while(current->get_next() != nullptr){
      current = current->get_next(); 
    }
    current->set_next(customer);
    current->get_next()->set_next(nullptr);
  }
  
}

Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue 
  // and return a pointer to it

  if (head == nullptr){
    return nullptr;
  }
  Customer* oldHead = head; 
  head = oldHead->get_next();
  
  return oldHead; 
  
}

int QueueList::get_items() {
  // count total number of items each customer in the queue has
  int totalItems = 0; 

  Customer* current = head;

  while (current != nullptr){
    totalItems += current->get_numOfItems();
    current = current->get_next();
  }

  return totalItems; 
}

bool QueueList::empty_queue() {
  // if the queue is empty, return false
  // if the queue is not empty, delete all customers
  // and return true

  Customer* current = head; 

  if (current == nullptr){
    return false; 
  }else{
    delete head; 
    return true; 
  }
  
}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
