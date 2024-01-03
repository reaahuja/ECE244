//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;

#include "Shape.h"

class Triangle : public Shape {
private:
    float x1, x2, x3, y1, y2, y3;                  // The radius of the circle

public:
    // Constructor
    Triangle (string n, float X1, float Y1, float X2, float Y2, float X3, float Y3);
    
    // Destructor
    virtual ~Triangle();
    
    // Accessor
    float getx1() const; 
    float getx2() const;  
    float getx3() const; 
    float gety1() const; 
    float gety2() const; 
    float gety3() const;  

    // Mutator
    void setx1(float val);       
    void setx2(float val); 
    void setx3(float val); 
    void sety1(float val); 
    void sety2(float val); 
    void sety3(float val); 
    
    // Utility methods
    virtual void draw() const;     // Draws thye circle; for the assignment it
                                   // prints the information of the circle
    
    virtual float computeArea() const;   // Computes the area of the circle
    
    virtual Shape* clone() const;  // Clones the object
};


// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.

#endif /* Triangle_h */


