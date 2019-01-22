//
// Martin Ethier, 20660931
//

#ifndef LAB_2_PATIENT_RECORD_H
#define LAB_2_PATIENT_RECORD_H

using namespace std;
#include <iostream>
#include <string>

class PatientRecord {
    string name;
    string address;
    string DOB;

    unsigned int categoryID;
    unsigned int patientID;

public:
    //constructors
    PatientRecord();
    PatientRecord(unsigned int newCatID, unsigned int newPatID, string newName, string newAddress, string newDOB);

    //destructor
    ~PatientRecord();

    //getters
    unsigned int getCatID();
    unsigned int getPatID();
    string getName();
    string getAddress();
    string getDOB();
};


#endif //LAB_2_PATIENT_RECORD_H
