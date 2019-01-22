//
// Martin Ethier, 20660931
//

#include "records_manager.h"
#include "patient_record.h"

//constructors
RecordsManager::RecordsManager() {
    capacity = 128;
    size = 0;
    data = new PatientRecord*[capacity];
}

RecordsManager::RecordsManager(int nCap) {
    nCap < 128 ? capacity = 128 : capacity = nCap;

    size = 0;
    data = new PatientRecord*[capacity];
}

RecordsManager::~RecordsManager() {
    delete [] data;
}

int RecordsManager::getSize() {
    return size;
}

int RecordsManager::getCapacity() {
    return capacity;
}

void RecordsManager::print() {
    if (size == 0) {
        cout << "Printing all patient records...\n\nRecords manager is empty, cannot print.\n";
    } else {
        cout << "Printing all patient records...\n\n";
        for (int i = 0; i < size; i ++) {
            cout << "Category ID: " << data[i]->getCatID() << endl;
            cout << "Patient ID: " << data[i]->getPatID() << endl;
            cout << "Name: " << data[i]->getName() << endl;
            cout << "Address: " << data[i]->getAddress() << endl;
            cout << "Date of birth: " << data[i]->getDOB() << endl << endl;
        }
    }
}

bool RecordsManager::insertRecord(unsigned int newCatID, unsigned int newPatID, string newName, string newAddress, string newDOB) {
    //check if there is a record with matching catID and patID
    for (int i = 0; i < size; i ++) {
        if (data[i]->getCatID() == newCatID && data[i]->getPatID() == newPatID) {
            cout << "There is already a record with this category and patient ID.\n";
            return false;
        }
    }

    //if size has reached capacity, double capacity, then reinitialize data array
    if (size == capacity) {
        capacity *= 2;
        PatientRecord** temp = data;
        data = new PatientRecord*[capacity];

        for (int i = 0; i < size; i ++) {
            data[i] = temp[i];
        }
    }

    //initialize new record object
    PatientRecord * newRecord = new PatientRecord(newCatID, newPatID, newName, newAddress, newDOB);

    //if size is 0, insert record at first index
    if (size == 0){
        data[0] = newRecord;
        size ++;
        return true;
    }

    //loop through list and insert if newCatID is <= and newPatID is <
    for (int i = 0; i < size; i ++) {
        if (newCatID < data[i]->getCatID() || (newCatID == data[i]->getCatID() && newPatID < data[i]->getPatID())) {
            //loop from end of data down to i, assign element to right index
            for (int j = size - 1; j >= i; j --) {
                data[j+1] = data[j];
            }
            data[i] = newRecord;
            size ++;
            return true;
        }
    }

    //if we run through loop without inserting, record must be inserted at end of list
    data[size] = newRecord;
    size ++;
    return true;
}

bool RecordsManager::removeRecord(unsigned int categoryID, unsigned int patientID) {
    //if manager is empty, return false
    if (size == 0) {
        cout << "Records manager is empty, no records available for removal.\n\n";
        return false;
    }

    //check if there is a record with matching catID and patID
    for (int i = 0; i < size; i ++) {
        if (data[i]->getCatID() == categoryID && data[i]->getPatID() == patientID) {
            //loop from i to size-1 and assign right element to index
            for (int j = i; j < size-1; j ++) {
                data[j] = data[j+1];
            }
            size --;

            //if size is now less than 1/4 capacity, halve capacity (cant go lower than 128)
            if (size == capacity/4 && capacity > 128) {
                capacity /= 2;
                PatientRecord** temp = data;
                data = new PatientRecord*[capacity];

                for (int i = 0; i < size; i ++) {
                    data[i] = temp[i];
                }
            }

            return true;
        }
    }

    //if run through loop without removing, record not found and returns false
    cout << "No record with matching category and patient ID found.\n\n";
    return false;
}

