
// Created by Salma Emara on 2023-06-02.
#include "Register.h"

#include <iostream>

Register::Register(int id, double timePerItem, double overhead,
                   double entryTime) {
  ID = id;
  secPerItem = timePerItem;
  overheadPerCustomer = overhead;
  availableTime = entryTime;
  next = nullptr;           // no other registers yet
  queue = new QueueList();  // no customers in line yet, but has to initialize a
                            // queue
}

Register::~Register() { 
  delete queue;
  delete next;
}

QueueList* Register::get_queue_list() { return queue; }

Register* Register::get_next() { return next; }

int Register::get_ID() { return ID; }

double Register::get_secPerItem() { return secPerItem; }

double Register::get_overheadPerCustomer() { return overheadPerCustomer; }

double Register::get_availableTime() { return availableTime; }

void Register::set_next(Register* nextRegister) { next = nextRegister; }


void Register::set_availableTime(double availableSince) {
  availableTime = availableSince;
}

double Register::calculateDepartTime() {
  // Get the departure time of the first customer in the queue
  // returns -1 if no customer is in the queue

  Customer* current = queue->get_head(); 
  if (current == nullptr){
    return -1;
  }else{
    double processingTime = (secPerItem * current->get_numOfItems()) + overheadPerCustomer; 
    double departureTime = 0;
    if (current->get_arrivalTime() > availableTime){
      departureTime = processingTime + current->get_arrivalTime(); 
    }else{
      departureTime = processingTime + availableTime; 
    }
    current->set_departureTime(departureTime);
    return departureTime;
  }
  
}

void Register::departCustomer(QueueList* doneList) {
  // dequeue the head, set last dequeue time, add to doneList,
  // update availableTime of the register

  //LAST DEQUEUE TIME?
  Customer* oldCustomer = queue->dequeue();
  if (oldCustomer != nullptr){
    availableTime = oldCustomer->get_departureTime();
    //  std::cout << "here 4" << std::endl;
    doneList->enqueue(oldCustomer);
    //  std::cout << "here 5" << std::endl;
  }
}

void Register::print() {
  std::cout << "Register ID: " << ID << std::endl;
  std::cout << "Time per item: " << secPerItem << std::endl;
  std::cout << "Overhead per customer: " << overheadPerCustomer << std::endl;
  if (queue->get_head() != nullptr) {
    std::cout << "Queue has customers: \n";
    queue->print();
  }
}
