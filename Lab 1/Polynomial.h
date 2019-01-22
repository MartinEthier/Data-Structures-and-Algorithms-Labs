/*
Polynomial.cpp
Created by Martin Ethier
ID: 20660931
*/

#ifndef Polynomial_hpp
#define Polynomial_hpp
#include <iostream>
using namespace std;

class Polynomial {
    int size;
	int *data = NULL;

public:
	//Constructors
    Polynomial(int A[], int size);
    Polynomial();
    Polynomial(string fileName);
    //Destructor
    ~Polynomial();
	
	//Methods
	void add(const Polynomial& second);
	void sub(const Polynomial& second);
	void mul(const Polynomial& second);
	//method to display polynomial
	void display();
	
};

#endif
