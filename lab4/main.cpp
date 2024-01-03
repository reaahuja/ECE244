#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:

// Set mode of the simulation
string getMode();
string mode;

// Register
void parseRegisterAction(stringstream &lineStream, string mode);
void openRegister(
    stringstream &lineStream,
    string mode);  // register opens (it is upto customers to join)
void closeRegister(stringstream &lineStream,
                   string mode);  // register closes 

// Customer
void addCustomer(stringstream &lineStream,
                 string mode);  // customer wants to join


// Helper functions
bool getInt(stringstream &lineStream, int &iValue);
bool getDouble(stringstream &lineStream, double &dValue);
bool foundMoreArgs(stringstream &lineStream);
void deleteAllMemory(RegisterList*, QueueList*, QueueList*);
void departCustomer();
void stats();

// Global variables
RegisterList *registerList; // holding the list of registers
QueueList *doneList; // holding the list of customers served
QueueList *singleQueue; // holding customers in a single virtual queue
double expTimeElapsed; // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> ";  // Prompt for input
  getline(cin, line);

  while (!cin.eof()) {
    stringstream lineStream(line);
    lineStream >> command;
    if (command == "register") {
      parseRegisterAction(lineStream, mode);
    } else if (command == "customer") {
      addCustomer(lineStream, mode);
    } else {
      cout << "Invalid operation" << endl;
    }
    cout << "> ";  // Prompt for input
    getline(cin, line);
  }

  stats();

  // You have to make sure all dynamically allocated memory is freed 
  // before return 0
  deleteAllMemory(registerList, doneList, singleQueue);

  return 0;
}

string getMode() {
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to "
          "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single") {
    cout << "Simulating a single queue ..." << endl;
  } else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
  }

  return mode;
}

void addCustomer(stringstream &lineStream, string mode) {
  int items;
  double timeElapsed;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments." << endl;
    return;
  }
  // Depending on the mode of the simulation (single or multiple),
  // add the customer to the single queue or to the register with
  // fewest items

  // cout << "Previous time: " << expTimeElapsed << endl;
  expTimeElapsed += timeElapsed;
  // cout << "Current time: " << expTimeElapsed << " due to: " << timeElapsed << endl;
  Customer* newCustomer = new Customer(expTimeElapsed, items);

  //depart a customer
  departCustomer();
  cout << "A customer entered" << endl; 
  if(mode == "single"){
    if(registerList != nullptr){
      Register* minReg = registerList->get_free_register();
      if(minReg != nullptr){
        QueueList* minRegQueue = minReg->get_queue_list();
        minRegQueue->enqueue(newCustomer);
        cout << "Queued a customer with free register " << minReg->get_ID() << endl;
      }else{
        singleQueue->enqueue(newCustomer);
        cout << "No free registers" << endl;
      }
    } 
  }else{
    if(registerList != nullptr){
      Register* minReg = registerList->get_min_items_register();
      if(minReg != nullptr){
        QueueList* minRegQueue = minReg->get_queue_list();
        minRegQueue->enqueue(newCustomer);
        cout << "Queued a customer with quickest register " << minReg->get_ID() << endl;
      }
    }
  }

}

void departCustomer(){

  if (registerList->get_head() == nullptr){
    return;
  }
  bool exit = false;
  int size = registerList->get_size();

  //cout << "Time elapsed" << expTimeElapsed << endl;
  while (!exit){
    Register* currentReg = registerList->get_head();
    Register* lowestReg = currentReg;
    double lowestValue = currentReg->calculateDepartTime();
    while (currentReg != nullptr){
      double currentRegDepart = currentReg->calculateDepartTime();
        // cout << "Comparing " << currentReg->get_ID() << " time " << (currentRegDepart) << endl; 
      if(currentRegDepart < lowestValue && currentRegDepart != -1 && lowestValue != -1){
        lowestValue = currentRegDepart; 
        lowestReg = currentReg;
      }else if (lowestValue == -1){
        lowestValue = currentRegDepart; 
        lowestReg = currentReg;
      }
      currentReg = currentReg->get_next();
    }
      // cout << "Lowest " << lowestReg->get_ID() << " time " << lowestValue << endl; 
    if (lowestValue <= expTimeElapsed && lowestValue != -1){
      lowestReg->departCustomer(doneList);
      cout << "Departed a customer at register ID " << lowestReg->get_ID() << " at " << lowestValue << endl;
      lowestReg->set_availableTime(lowestValue);

      if(mode == "single"){
        if(registerList != nullptr){
          Register* freeReg = registerList->get_free_register();
          Customer* newFirst = singleQueue->dequeue();
          if(freeReg != nullptr && newFirst != nullptr){
            QueueList* freeRegQueue = freeReg->get_queue_list();
            freeRegQueue->enqueue(newFirst);
            cout << "Queued a customer with free register " << freeReg->get_ID() << endl;
           }//else{
          //   cout << "No free registers" << endl; NOT SURE
          // }
        }  
      }
    }else{
      exit = true;
    }
  }
}




void parseRegisterAction(stringstream &lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  } else if (operation == "close") {
    closeRegister(lineStream, mode);
  } else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream &lineStream, string mode) {
  int ID;
  double secPerItem, setupTime, timeElapsed;
  // convert strings to int and double
  if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
      !getDouble(lineStream, setupTime) ||
      !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if the register is already open
  // If it's open, print an error message
  // Otherwise, open the register
  // If we were simulating a single queue, 
  // and there were customers in line, then 
  // assign a customer to the new register
  bool registerExists = registerList->foundRegister(ID);
  if(registerExists){
    cout << "Error: register " << ID << " is already open" << endl;
  }else{
    expTimeElapsed += timeElapsed;
    departCustomer();  //NOT SURE IF ONLY FOR SINGLE
    Register* newReg = new Register(ID, secPerItem, setupTime, expTimeElapsed);
    registerList->enqueue(newReg);

    cout << "Opened register " << ID << endl; 

    //assign customers to new register 
    if(mode == "single" && singleQueue->get_head() != nullptr){
      Customer* customer = singleQueue->dequeue();
      QueueList* queue = newReg->get_queue_list();
      queue->enqueue(customer);

      cout << "Queued a customer with free register " << ID << endl;

    }
  }

}

void closeRegister(stringstream &lineStream, string mode) {
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if the register is open
  // If it is open dequeue it and free it's memory
  // Otherwise, print an error message 


  Register* current = registerList->get_head();
  bool found = false;
  expTimeElapsed += timeElapsed;
  if (current != nullptr){
    while(current != nullptr && !found){
      if(current->get_ID() == ID){
        departCustomer();
        delete registerList->dequeue(ID);
        found = true;
        cout << "Closed register " << ID << endl;
      }
      current = current->get_next();
    }
  }

  if (!found){
    cout << "Error: register " << ID << " is not open" << endl;
    //need to find error message
  }

}

bool getInt(stringstream &lineStream, int &iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream &lineStream, double &dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream &lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  } else {
    return true;
  }
}

void deleteAllMemory(RegisterList* registerList, QueueList* doneList, QueueList* singleQueue){
  //delete single queue
  //singleQueue->empty_queue();

  // //delete all gone customers
  //doneList->empty_queue();

  // //delete all queues with customers if they still contain customers
  // Register* current = registerList->get_head(); 
  // while(current != nullptr){
  //   current->get_queue_list()->empty_queue();
  //   current = current->get_next();
  // }

  //delete all registers 
  delete doneList;
  delete singleQueue;
  delete registerList;
}

void stats(){
  cout << "Finished at time " << expTimeElapsed << endl;
  cout << "Statistics: " << endl;

  Customer* current = doneList->get_head();
  if (current != nullptr){
    double maxWait = current->get_departureTime() - current->get_arrivalTime();
    double avgWait = 0;
    int totalCustomers = 0;
    while (current != nullptr){
      double wait = current->get_departureTime() - current->get_arrivalTime();
      if (wait > maxWait){
        maxWait = wait;
      }
      // cout << "Wait: " << wait << endl;
      avgWait += wait;
      totalCustomers++;

      current = current -> get_next();
    }

        // cout << "totalcustomers: " << totalCustomers << endl;


    avgWait /= totalCustomers;

    current = doneList->get_head();
    double standardDev = 0;
    while (current != nullptr){
      standardDev += pow(((current->get_departureTime() - current->get_arrivalTime()) - avgWait), 2);
      current = current -> get_next();
    }
    standardDev = sqrt((standardDev/totalCustomers));


    cout << "Maximum wait time: " << maxWait << endl;
    cout << "Average wait time: " << avgWait << endl;
    cout << "Standard Deviation of wait time: " << standardDev << endl;
  }else{
    cout << "Maximum wait time: 0" << endl;
    cout << "Average wait time: -nan" << endl;
    cout << "Standard Deviation of wait time: -nan" << endl;
  }
  
}

// void departCustomer(){

//   if (registerList->get_head() == nullptr){
//     return;
//   }
//   bool exit = false;
//   bool change = false;
//   int size = registerList->get_size();

//   while (!exit){
//     Register* currentReg = registerList->get_head();
//     if (change){
//       int counter = registerList->get_size() - size;
//       while((counter != 0) && currentReg != nullptr){
//         currentReg = currentReg->get_next();
//         counter--;
//       }
//     }
//     Register* lowestReg = currentReg;
//     int lowestValue = currentReg->calculateDepartTime();
//     while (currentReg != nullptr && lowestValue != -1){
//       int currentRegDepart = currentReg->calculateDepartTime();
//       if(currentRegDepart < lowestValue && currentRegDepart != -1){
//         lowestValue = currentRegDepart; 
//         lowestReg = currentReg;
//       }
//       currentReg = currentReg->get_next();
//     }

//     if (lowestValue < expTimeElapsed && lowestValue != -1){
//       lowestReg->departCustomer(doneList);
//       cout << "Departed a customer at register ID " << lowestReg->get_ID() << " at " << lowestValue << endl;
//       lowestReg->set_availableTime(lowestValue);
//     }else if(size > 1 && currentReg != nullptr){
//       change = true;
//       size--;
//     }else{
//       exit = true;
//     }
//   }
// }

