//
// Martin Ethier, 20660931
//

#ifndef LAB_2_RECORDS_MANAGER_H
#define LAB_2_RECORDS_MANAGER_H

using namespace std;
#include <iostream>
#include <string>
#include "patient_record.h"

class RecordsManager {
    int size;
    int capacity;
    PatientRecord** data = nullptr;

    friend class RecordsManagerTest;
public:
    //constructors
    RecordsManager();
    RecordsManager(int nCap);

    //destructor
    ~RecordsManager();

    //getters
    int getSize();
    int getCapacity();

    //printers
    void print();

    //record manipulation
    bool insertRecord(unsigned int newCatID, unsigned int newPatID, string newName, string newAddress, string newDOB);
    bool removeRecord(unsigned int categoryID, unsigned int patientID);

};


#endif //LAB_2_RECORDS_MANAGER_H
