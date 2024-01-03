//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
bool commandValidation(string command, stringstream& linestream);
void checkANDexecute(string command, stringstream& lineStream);
void checkValue(int var, bool& errorRaised, bool& continueInput);


// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int main() {

    string line;
    string command;

    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        bool validCommand = commandValidation(command, lineStream);
        if (validCommand){
            checkANDexecute(command, lineStream);
        }else{
            cout << "Error: invalid command" << endl;
        }


        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);

    }  // End input loop until EOF.

    return 0;
}

//only validates command 
bool commandValidation(string command, stringstream& linestream){
    //JUST ADDED

    if(linestream.fail()){
        return false;
    }else if(command == "maxShapes" || command == "create" || command == "move" || command == "rotate" || command == "draw" || command == "delete" || command == "all"){
        return true;
    }else{
        return false;
    }
}

void checkANDexecute(string command, stringstream& lineStream){
    bool continueInput = true;
    bool takeInput = true;
    bool errorRaised = false;
    if (command == "maxShapes"){
        int temp = 0;
        int value = -1; 
        while(continueInput){
            lineStream >> value; 
            if (lineStream.fail()){
                continueInput = false; 
                if(lineStream.eof()){
                    if (value == -1){
                        cout << "Error: too few arguments" << endl; 
                        errorRaised = true; 
                    }
                }else{
                    cout << "Error: invalid value" << endl;
                    errorRaised = true; 
                }
            }else{
                if (value >= 0 && takeInput){
                    temp = value;
                    takeInput = false;
                }else if(!takeInput){
                    cout << "Error: too many arguments" << endl; 
                    continueInput = false; 
                    errorRaised = true; 
                }else{
                    //value is less then 0
                    cout << "Error: invalid value" << endl;
                    continueInput = false;
                    errorRaised = true; 
                }

            }
        }

        //if there was no error then initialize the shapesArray 
        if(!errorRaised){
            if (max_shapes != 0){
                if (shapesArray != nullptr){
                    for (int i = 0; i < max_shapes; i++){
                        if (shapesArray[i] != nullptr){
                            delete shapesArray[i];
                            shapesArray[i] = nullptr;
                        }
                    }
                    delete []shapesArray;
                    shapesArray = nullptr;
                    shapeCount = 0;
                }
            }

            max_shapes = temp;
            shapesArray = new Shape*[max_shapes];

            for (int i = 0; i < max_shapes; i ++){
                shapesArray[i] = nullptr;
            }
            cout << "New database: max shapes is " << max_shapes << endl;
        }
    }else if(command == "create"){
        string name = "";
        string type = "";
        int x_loc = -1; 
        int y_loc = -1;
        int x_size = -1;
        int y_size = -1; 
        int counter = 6;
        int peek = 0;

        while(continueInput){
            if (counter == 6){
                lineStream >> name;
            }else if(counter == 5){
                lineStream >> type; 
            }else if(counter == 4){
                lineStream >> x_loc;
            }else if(counter == 3){
                lineStream >> y_loc;
            }else if(counter == 2){
                lineStream >> x_size;
            }else if(counter == 1){
                lineStream >> y_size;
            }else{
                lineStream >> peek;
            }

            if(lineStream.fail()){
                if(!lineStream.eof()){
                    if (counter >= 1){
                        cout << "Error: invalid argument" << endl; 
                        errorRaised = true;
                    }else{
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    } 
                }else{
                    //end reached
                    if (counter > 0){
                        cout << "Error: too few arguments" << endl;
                        errorRaised = true; 
                    }else if (counter < 0){
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    }
                }
                continueInput = false; 
            }else{
                counter--; 
            }

            if(continueInput){
                if(counter < 6){
                    //reserved keyword, name exists
                    bool aCommand = commandValidation(name, lineStream);
                    if (aCommand || name == "ellipse" || name == "circle" || name == "rectangle" || name == "triangle"){
                        cout << "Error: invalid shape name" << endl;
                        errorRaised = true; 
                        continueInput = false; 
                    }else{
                        for (int i = 0; i < max_shapes; i++){
                            if (shapesArray[i] != nullptr){
                                if ((shapesArray[i])->getName() == name){
                                    cout << "Error: shape " << name << " exists" << endl;
                                    errorRaised = true; 
                                    continueInput = false;
                                    i = max_shapes;
                                }
                            }
                        }
                    }
                }

                if(counter < 5){
                    if(type != "ellipse" && type != "circle" && type != "rectangle" && type != "triangle"){
                        cout << "Error: invalid shape type" << endl;
                        errorRaised = true; 
                        continueInput = false;
                    }
                }
                if (counter < 4){
                    checkValue(x_loc, errorRaised, continueInput);
                }
                if(counter < 3){
                    checkValue(y_loc, errorRaised, continueInput);
                }
                if(counter < 2){
                    checkValue(x_size, errorRaised, continueInput);
                }
                if(counter < 1){ //JUST CHANGED

                    checkValue(y_size, errorRaised, continueInput);

                    char temp = lineStream.peek();
                    if (continueInput){
                        if (isdigit(temp) || isspace(temp) || temp == EOF || temp == ' '){
                            if ((x_size != y_size) && type == "circle"){
                                cout << "Error: invalid value" << endl;
                                errorRaised = true; 
                                continueInput = false;
                            }
                        }else{
                            if (temp != ' ' && !isspace(temp) && temp != 32){
                                cout << "Error: invalid argument" << endl; 
                                errorRaised = true; 
                                continueInput = false;
                            }

                        }
                    }


                    //  if (type == "circle" && continueInput){
                    //     if (x_size != y_size){
                    //         cout << "Error: invalid value" << endl;
                    //         errorRaised = true; 
                    //         continueInput = false;
                    // }
                    // }

                    // char temp = lineStream.peek();

                    // if (type == "circle" && continueInput){
                    //     char temp = lineStream.peek();
                    //     if (isdigit(temp) || isspace(temp) || temp == EOF){
                    //         if (x_size != y_size){
                    //             cout << "Error: invalid value" << endl;
                    //             errorRaised = true; 
                    //             continueInput = false;
                    //         }
                    //     }else{
                    //         cout << "Error: invalid argument" << endl; 
                    //         errorRaised = true; 
                    //         continueInput = false;
                    //     }
                    // }

                    // if (temp < 30 || temp > 39){
                    //     cout << "Error: invalid argument" << endl; 
                    //     errorRaised = true; 
                    //     continueInput = false;
                    // }else{
                    //     if (type == "circle"){
                    //     if (x_size != y_size){
                    //         cout << "Error: invalid value" << endl;
                    //         errorRaised = true; 
                    //         continueInput = false;
                    //     }
                    //     }
                    // }

                }
            }

        }
        if(!errorRaised){
            if(shapeCount == max_shapes){
                cout << "Error: shape array is full" << endl;
            }else{
                shapesArray[shapeCount] = new Shape(name, type, x_loc, x_size, y_loc, y_size);
                cout << "Created ";
                shapesArray[shapeCount]->draw();
                cout << endl;
                shapeCount++;
            }
        }
    }else if(command == "move"){
        string name = "";
        int peeky;
        int loc1 = -1; 
        int loc2 = -1; 
        int counter = 3;
        int location = -1;

        while(continueInput){
            if (counter == 3){
                lineStream >> name; 
            }else if(counter == 2){
                lineStream >> loc1; 
            }else if(counter == 1){
                lineStream >> loc2;
            }else{
                lineStream >> peeky;
            }

            if(lineStream.fail()){
                if(!lineStream.eof()){
                    if (counter >= 1){
                        cout << "Error: invalid argument" << endl; 
                        errorRaised = true;
                    }else{
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    } 
                }else{
                    //end reached
                    if (counter > 0){
                        cout << "Error: too few arguments" << endl;
                        errorRaised = true; 
                    }else if (counter < 0){
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    }
                }
                continueInput = false; 
            }else{
                counter--; 
            }

            if (continueInput == true){
                if (counter < 3){
                    //check name
                    bool foundName = false;
                    for (int i = 0; i < max_shapes; i++){
                        if (shapesArray[i] != nullptr && shapesArray[i]->getName() == name){
                            foundName = true;
                            location = i;
                        }
                    }
                    if (foundName == false){
                        cout << "Error: shape " << name << " not found" << endl;
                        continueInput = false;  errorRaised = true;
                    }
                }

                if (counter < 1){
                    if (loc1 < 0 || loc2 < 0){
                        cout << "Error: invalid value" << endl;
                        continueInput = false;  errorRaised = true;
                    }
                }
            }

        }

        if (!errorRaised && location != -1){
            shapesArray[location]->setXlocation(loc1);
            shapesArray[location]->setYlocation(loc2);
            cout << "Moved " << name << " to " << loc1 << " " << loc2 <<endl;
        }
    }else if(command == "rotate"){
        string name = "";
        int extra = 0;
        int angle = -1; 
        int counter = 2;
        int location = -1;

        while (continueInput){
            if(counter == 2){
                lineStream >> name;
            }else if(counter == 1){
                lineStream >> angle;
            }else{
                lineStream >> extra;
            }

            if(lineStream.fail()){
                if(!lineStream.eof()){
                    if (counter >= 1){
                        cout << "Error: invalid argument" << endl; 
                        errorRaised = true;
                    }else{
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    } 
                }else{
                    //end reached
                    if (counter > 0){
                        cout << "Error: too few arguments" << endl;
                        errorRaised = true; 
                    }else if (counter < 0){
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    }
                }
                continueInput = false; 
            }else{
                counter--; 
            }

            if(counter < 2){
                //check name
                bool found = false;
                for (int i = 0; i < max_shapes; i++){
                    if (shapesArray[i] != nullptr && (shapesArray[i]->getName() == name)){
                        found = true;
                        location = i;
                    }
                }
                if (!found){
                    cout << "Error: shape " << name << " not found" << endl; 
                    errorRaised = true; continueInput = false;
                }
            }
            if (counter <1){
                //check rotation 
                if (angle < 0 || angle > 360){
                    cout << "Error: invalid value" << endl; 
                    errorRaised = true; continueInput = false;
                }
            }
        }


        if (!errorRaised && location != -1){
            shapesArray[location]->setRotate(angle);
            cout << "Rotated " << name << " by " << angle << " degrees" << endl;
        }
    }else if(command == "draw"){
        string name = "";
        int extra = 0;
        int counter = 1;
        int location = -1;
        while(continueInput){
            if(counter == 1){
                lineStream >> name;
            }else{
                lineStream >> extra;
            }

            if(lineStream.fail()){
                if(!lineStream.eof()){
                    if (counter >= 1){
                        cout << "Error: invalid argument" << endl; 
                        errorRaised = true;
                    }else{
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    } 
                }else{
                    //end reached
                    if (counter > 0){
                        cout << "Error: too few arguments" << endl;
                        errorRaised = true; 
                    }else if (counter < 0){
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    }
                }
                continueInput = false; 
            }else{
                counter--; 
            }

            if (counter < 1){
                if (name != "all"){
                    //if the name is not all check if its a shape
                    bool found = false;
                    for (int i = 0; i < max_shapes; i++){
                        if (shapesArray[i] != nullptr && (shapesArray[i]->getName() == name)){
                            found = true;
                            location = i; 
                        }
                    }

                    if (!found){
                        cout << "Error: shape " << name << " not found" << endl;
                        errorRaised = true; continueInput = false;
                    }
                }
            }
        }

        if (!errorRaised){
            if (name == "all"){
                cout << "Drew all shapes " << endl;
                bool extraspace = false;
                for (int i = 0; i < max_shapes; i++){
                    if(shapesArray[i] != nullptr){
                        shapesArray[i]->draw();
                        extraspace = true;
                    }
                }
                if(extraspace){
                    cout << endl;
                }
            }else{
                cout << "Drew ";
                shapesArray[location]->draw();
                cout << endl;
            }
        }
    }else{
    //command == "delete"
        string name = "";
        int extra = 0;
        int counter = 1;
        int location = -1;
        while(continueInput){
            if(counter == 1){
                lineStream >> name;
            }else{
                lineStream >> extra;
            }

            if(lineStream.fail()){
                if(!lineStream.eof()){
                    if (counter >= 1){
                        cout << "Error: invalid argument" << endl; 
                        errorRaised = true;
                    }else{
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    } 
                }else{
                    //end reached
                    if (counter > 0){
                        cout << "Error: too few arguments" << endl;
                        errorRaised = true; 
                    }else if (counter < 0){
                        cout << "Error: too many arguments" << endl;
                        errorRaised = true; 
                    }
                }
                continueInput = false; 
            }else{
                counter--; 
            }

            if (counter < 1){
                if (name != "all"){
                    //if the name is not all check if its a shape
                    bool found = false;
                    for (int i = 0; i < max_shapes; i++){
                        if (shapesArray[i] != nullptr && (shapesArray[i]->getName() == name)){
                            found = true;
                            location = i; 
                        }
                    }

                    if (!found){
                        cout << "Error: shape " << name << " not found" << endl;
                        errorRaised = true; continueInput = false;
                    }
                }
            }
        }

        if (!errorRaised){
            if (name == "all"){
                //delete all shapes
                if (shapesArray != nullptr){
                    for (int i = 0; i < max_shapes; i++){
                        if (shapesArray[i] != nullptr){
                            delete shapesArray[i];
                            shapesArray[i] = nullptr;
                        }
                    }
                }
                shapeCount = 0; //JUST ADDED

                cout << "Deleted: all shapes" << endl;
            }else{
                //delete a single shape
                delete shapesArray[location];
                shapesArray[location] = nullptr;
                cout << "Deleted shape " << name << endl;
            }
        }
    }
}

void checkValue(int var, bool& errorRaised, bool& continueInput){
    if (var < 0){
        cout << "Error: invalid value" << endl;
        errorRaised = true; 
        continueInput = false;
    }
}
