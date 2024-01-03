#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  // Delete all registers in the list

  // Register* current = head; 
  // if (current->get_next() == nullptr){
  //   delete current;
  // }else{
  //   while(current!= nullptr){
  //     Register* temp = current;
  //     current = current->get_next();
  //     delete temp;
  //   }
  // }

  delete head;
}

Register* RegisterList::get_head() {  return head; }

int RegisterList::get_size() { 
  // return number of registers 
  int counter = 0; 
  Register* current = head; 

  while (current != nullptr){
    counter++; 
    current = current->get_next();
  }

  return counter; 
}


Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items
  int lowestItems; 
  Register* current = head; 
  Register* lowestReg = nullptr; 

  while (current != nullptr){
    int registerItems = 0; 
    QueueList* customerCurrent = current->get_queue_list();
    if(customerCurrent != nullptr){
      registerItems += customerCurrent->get_items();
    }

    if(current == head){
      lowestItems = registerItems;
      lowestReg = current;
    }else{
      if (registerItems < lowestItems){
        lowestItems = registerItems;
        lowestReg = current;
      }
    }

    current = current->get_next();
  }

  return lowestReg; 
}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr
  Register* current = head; 

  while(current != nullptr){
    QueueList* currentQueue = current->get_queue_list(); 
    if(currentQueue == nullptr || currentQueue->get_head() == nullptr){
      return current;
    }
    current = current->get_next();
  }

  return nullptr; 
}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size 
  
  if(newRegister->get_queue_list() == nullptr){
    //new register becomes the head 
    if(head == nullptr){
      head = newRegister;
    }else{
      newRegister->set_next(head->get_next());
      head = newRegister; 
    }
  }else{
    //register is placed at end of queue
    if (head == nullptr){
      head = newRegister;
    }else{
       Register* current = head; 
       while(current->get_next() != nullptr){
        current = current->get_next();
       }
       current->set_next(newRegister);
    }
  }

  size++;
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  Register* current = head; 
  while(current != nullptr){
    if(current->get_ID() == ID){
      return true; 
    }
    current = current -> get_next();
  }

  return false; 
}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID
  Register* current = head; 

  if (current!= nullptr && current->get_ID() == ID){
    head = current->get_next(); 
    current->set_next(nullptr);
    return current; 
  }else{
    while(current != nullptr && current->get_next() != nullptr){
      if(current->get_next()->get_ID() == ID){
        Register* temp = current; 
        Register* deleting = current->get_next(); 

        temp->set_next(deleting->get_next());
        deleting->set_next(nullptr);
        return deleting;
      }
      current = current->get_next();
    }
  }

  return nullptr;
  // return the dequeued register
  // return nullptr if register was not found
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr

  //NOT SURE

  Register* current = head; 
  Register* lowestReg = nullptr; 
  double departTime = 0; 
  double lowestTime; 

  while(current != nullptr){
    if (current == head){
      lowestTime = current->calculateDepartTime(); 
      lowestReg = head; 
    }else{
      double currentTime = current->calculateDepartTime();
      if (currentTime < lowestTime && currentTime >= expTimeElapsed){
        lowestTime = currentTime;
        lowestReg = current; 
      }
    }
    current = current->get_next();
  }

  return lowestReg; 


}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
