//
// Martin Ethier, 20660931
//

#include "patient_record.h"

PatientRecord::PatientRecord()
        : categoryID(0), patientID(0), name(""), address(""), DOB("")
{}

PatientRecord::PatientRecord(unsigned int newCatID, unsigned int newPatID, string newName, string newAddress,
                             string newDOB)
        : categoryID(newCatID), patientID(newPatID), name(newName), address(newAddress), DOB(newDOB)
{}

PatientRecord::~PatientRecord() {}

unsigned int PatientRecord::getCatID() {
    return categoryID;
}

unsigned int PatientRecord::getPatID() {
    return patientID;
}

string PatientRecord::getName() {
    return name;
}

string PatientRecord::getAddress() {
    return address;
}

string PatientRecord::getDOB() {
    return DOB;
}

