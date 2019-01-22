/*
Polynomial.cpp
Created by Martin Ethier
ID: 20660931
*/

using namespace std;
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>

#include "Polynomial.h"

Polynomial::Polynomial(int A[], int inSize) {	
	data = new int[inSize];
	
	size = inSize;
	data = A;	
}

Polynomial::Polynomial(void) {
	//initialize size and assign random value between 1 and 10	
	size = rand() % 10 + 1;
	
	data = new int[size];
	
	//initialize coefficients, assign random value between -10 and 10 for each element
	for (int i = 0; i < size; i++) {
		data[i] = rand() % 21 + (-10);
	}
}

Polynomial::Polynomial(string fileName) {
	ifstream inputData;
	inputData.open(fileName.c_str());
	
	//read first line of file to get size
	inputData >> size;

	data = new int[size];
	
	//go through file and assign coefficients to data
	for (int i = 0; i < size; i ++) {
		inputData >> data[i];
	}

}

Polynomial::~Polynomial() {
	delete [] data;
	data = NULL;
}

void Polynomial::add(const Polynomial& second) {
	//define size as largest of both input sizes
	int sumSize = max(second.size, size);
	int sum[sumSize] = {0};

	//assign each element of first polynomial to sum
	for (int i = 0; i < size; i ++) {
		sum[i] = data[i];
	}

	//add second array element by element
	for (int i = 0; i < second.size; i ++) {
		sum[i] += second.data[i];
	}
	size = sumSize;
	//delete current memory allocated for data on heap
	delete [] data;
	//reinitialize and assign sum
	data = new int[size];
	for (int i = 0; i < size; i ++) {
		data[i] = sum[i];
	}
}

void Polynomial::sub(const Polynomial& second) {
	//define size as largest of both input sizes
	int diffSize = max(second.size, size);
	int diff[diffSize] = {0};
	
	//assign each element of first polynomial to diff
	for (int i = 0; i < size; i ++) {
		diff[i] = data[i];
	}

	//subtract second array element by element
	for (int i = 0; i < second.size; i ++) {
		diff[i] -= second.data[i];
	}	
	size = diffSize;
	//delete current memory allocated for data on heap
	delete [] data;
	//reinitialize and assign diff
	data = new int[size];
	for (int i = 0; i < size; i ++) {
		data[i] = diff[i];
	}
}

void Polynomial::mul(const Polynomial& second) {
	//define size of product as sum of both sizes minus 1
	int prodSize = size + second.size - 1;
	int prod[prodSize] = {0}; 
	
	//loop through both arrays and add on product of each element
	for (int i = 0; i < size; i ++) {
		for (int j = 0; j < second.size; j++) {
			prod[i+j] += data[i] * second.data[j];
		}
	}  			
	size = prodSize;
	//delete current memory allocated for data on heap
	delete [] data;
	//reinitialize and assign prod
	data = new int[size];
	for (int i=0;i<size;i++) {
		data[i] = prod[i];
	}	
}

void Polynomial::display() {
	//display 0 if polynomial is empty
	if (size == 0) {
		cout << 0;
	} else {
		//loop through and display as a regular polynomial
		cout << data[0] << "x^0";
		for (int i = 1; i < size; i ++) {
			cout << " + " << data[i] << "x^" << i;
		}	
	}
}

//Test functions
void test1() {
	//Testing out add method
	cout << "Testing out addition method..." << endl << endl;
	cout << "Test 1 (2 user defined polynomials): " << endl;
	int A[4] = {1,0,0,2}, B[1] = {3};
	
	Polynomial polyA(A,4),polyB(B,1);
	cout << "Adding ";
	polyB.display();
	cout << " to ";
	polyA.display();

	cout << "..." << endl << "Answer: ";
	polyA.add(polyB);
	polyA.display();
	
	cout << endl << endl << "Test 2 (1 user defined and 1 random polynomial):" << endl;
	int C[4] = {-3,0,6,-1};
	
	Polynomial polyC(C,4),polyD;
	cout << "Adding ";
	polyD.display();
	cout << " to ";
	polyC.display();

	cout << "..." << endl << "Answer: ";
	polyC.add(polyD);
	polyC.display();
	
	cout << endl << endl << "Test 3 (1 user defined and 1 file input polnomial):" << endl;
	int E[2] = {3,-2};
	
	Polynomial polyE(E,2),polyF("test1.txt");
	cout << "Adding ";
	polyF.display();
	cout << " to ";
	polyE.display();

	cout << "..." << endl << "Answer: ";
	polyE.add(polyF);
	polyE.display();
	cout << endl << endl;
}

void test2() {
	//Testing out sub method
	cout << "Testing out subtraction method..." << endl << endl;
	cout << "Test 1 (2 user defined polynomials): " << endl;
	int A[7] = {1,6,7,0,0,0,-3}, B[0] = {};
	
	Polynomial polyA(A,7),polyB(B,0);
	cout << "Subtracting ";
	polyB.display();
	cout << " from ";
	polyA.display();

	cout << "..." << endl << "Answer: ";
	polyA.sub(polyB);
	polyA.display();
	
	cout << endl << endl << "Test 2 (1 user defined and 1 random polynomial):" << endl;
	int C[4] = {-3,0,6,-1};
	
	Polynomial polyC(C,4),polyD;
	cout << "Subtracting ";
	polyD.display();
	cout << " from ";
	polyC.display();

	cout << "..." << endl << "Answer: ";
	polyC.sub(polyD);
	polyC.display();
	
	cout << endl << endl << "Test 3 (1 user defined and 1 file input polnomial):" << endl;
	int E[4] = {1,0,0,2};
	
	Polynomial polyE(E,4),polyF("test2.txt");
	cout << "Subtracting ";
	polyF.display();
	cout << " from ";
	polyE.display();

	cout << "..." << endl << "Answer: ";
	polyE.sub(polyF);
	polyE.display();
 	cout << endl << endl;
}

void test3() {
	//Testing out mul method
	cout << "Testing out multiplication method..." << endl << endl;
	cout << "Test 1 (2 user defined polynomials): " << endl;
	int A[4] = {1,0,0,2}, B[2] = {9,3};
	
	Polynomial polyA(A,4),polyB(B,2);
	cout << "Multiplying ";
	polyB.display();
	cout << " with ";
	polyA.display();

	cout << "..." << endl << "Answer: ";
	polyA.mul(polyB);
	polyA.display();
	
	cout << endl << endl << "Test 2 (1 user defined and 1 random polynomial):" << endl;
	int C[4] = {-3,0,6,-1};
	
	Polynomial polyC(C,4),polyD;
	cout << "Multiplying ";
	polyD.display();
	cout << " with ";
	polyC.display();

	cout << "..." << endl << "Answer: ";
	polyC.mul(polyD);
	polyC.display();
	
	cout << endl << endl << "Test 3 (1 user defined and 1 file input polnomial):" << endl;
	int E[3] = {1,0,-1};
	
	Polynomial polyE(E,3),polyF("test3.txt");
	cout << "Multiplying ";
	polyF.display();
	cout << " with ";
	polyE.display();

	cout << "..." << endl << "Answer: ";
	polyE.mul(polyF);
	polyE.display();
	cout << endl << endl;
}

int main() {
	//test addition method
	test1();
	
	//test subtraction method
	test2();
	
	//test multiplication method
	test3();

    return 0;
}


