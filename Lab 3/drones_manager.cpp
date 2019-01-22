//
// Martin Ethier, ID: 20660931
//
#include <iostream>
#include "drones_manager.hpp"

DronesManager::DronesManager() : size(0), first(nullptr), last(nullptr) {}

DronesManager::~DronesManager() {
    while (first) { // keep going while first is not NULL
        DroneRecord* temp = first; // store a pointer to first
        first = first->next; // change first to point to next
        delete temp; // delete temp and iterate
    }
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
    return size == 0;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (size == 0 || index >= size - 1) return *last;

	unsigned int i = 0;
	DroneRecord* current = first;
	while (i < index) {
	    current = current->next;
	    i++;
	}

	return *current;
}

unsigned int DronesManager::search(DroneRecord value) const {
    if (size == 0) return 0; // check for empty manager

    unsigned int index = 0;
    DroneRecord* current = first; // initialize end pointer
    while (current != nullptr) { // iterate until NULL
        if (*current == value) {
            return index;
        }
        index++;
        current = current->next;
    }
    return size;
}

void DronesManager::print() const {
    if (size == 0) return; // check for empty manager

    cout << "("; // print the header data
    DroneRecord* current = first; // initialize end pointer
    while (current != nullptr) { // iterate until nullptr
        cout << "[Drone ID: " << current->droneID << ", Range: " << current->range << ", Year Bought: " <<
             current->yearBought << ", Drone Type: " << current->droneType << ", Manufacturer: " <<
             current->manufacturer << ", Description: " << current->description << ", Battery Type: " <<
             current->batteryType << "]"; // print node
        current = current->next;
        if (current != nullptr) // print -> symbol between nodes
            cout << "->";
    }
    cout << ")\n"; // print the footer data
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	return lhs.droneID == rhs.droneID;
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    //check if value is unique
    DroneRecord* current = first;
    while (current != nullptr) {
        if (current == &value) {
            return false;
        }
        current = current->next;
    }

    if (index > size) {
        return false;
    } else if (size == 0) {
        first = &value;
        first->next = nullptr;
        first->prev = nullptr;
        last = first;
        size++;
        return true;
    } else if (index == 0) {
        DroneRecord* start = first;

        start->prev = &value;
        value.next = start;
        value.prev = nullptr;
        first = &value;

        size++;
        return true;
    } else {
        DroneRecord* current = first;
        unsigned int i = 0;
        //set current to node before index
        while (i < index - 1) {
            current = current->next;
            i++;
        }

        DroneRecord* new_rec = &value;

        new_rec->next = current->next;
        current->next = new_rec;
        new_rec->prev = current;

        if (new_rec->next != nullptr)
            new_rec->next->prev = new_rec;

        if (index == size) {
            last = new_rec;
        }
        size++;
        return true;
    }
}

bool DronesManager::insert_front(DroneRecord value) {
    //check if value is unique
    DroneRecord* current = first;
    while (current != nullptr) {
        if (current == &value) {
            return false;
        }
        current = current->next;
    }

    if (size == 0) { //empty list
	    first = &value;
	    first->next = nullptr;
	    first->prev = nullptr;
	    last = first;
	} else { //non-empty list
        DroneRecord* start = first;

        start->prev = &value;
        value.next = start;
        value.prev = nullptr;
        first = &value;
	}

    size++;
    return true;
}

bool DronesManager::insert_back(DroneRecord value) {
    //check if value is unique
    DroneRecord* current = first;
    while (current != nullptr) {
        if (current == &value) {
            return false;
        }
        current = current->next;
    }

    if (size == 0) { //empty list
        first = &value;
        first->next = nullptr;
        first->prev = nullptr;
        last = first;
    } else { //non-empty list
        DroneRecord* end = last;

        end->next = &value;
        value.next = nullptr;
        value.prev = end;
        last = &value;
    }

    size++;
    return true;
}

bool DronesManager::remove(unsigned int index) {
    if (size == 0 || index > size - 1) {
        return false;
    } else if (size == 1) {
        delete first;
        first = nullptr;
        last = nullptr;
        size--;
        return true;
    } else {
        DroneRecord* current = first; // initialize end pointer
        unsigned int i = 0;
        while (current != nullptr) { // iterate until NULL
            if (i == index) {
                current->prev->next = current->next;
                current->next->prev = current->prev;

                delete current;
                size--;
                return true;
            }
            current = current->next;
            i++;
        }
    }
}

bool DronesManager::remove_front() {
    if (size == 0) { // base case: empty list
        return false; // nothing to do

    } else if (size == 1) { // base case: list with one node
        delete first;
        first = nullptr;
        last = nullptr;

    } else { // general case: a list with more than one node
        DroneRecord* start = first->next; //assign second to last

        delete start->prev;
        start->prev = nullptr;

        first = start;
    }

    size--; // update size
    return true; // return true
}

bool DronesManager::remove_back() {
    if (size == 0) { // base case: empty list
        return false; // nothing to do

    } else if (size == 1) { // base case: list with one node
        delete first;
        first = nullptr;
        last = nullptr;

    } else { // general case: a list with more than one node
        DroneRecord* end = last->prev; //assign second to last

        delete end->next;
        end->next = nullptr;

        last = end;
    }

    size--; // update size
    return true; // return true

}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    //check if value is unique
    DroneRecord* current = first;
    while (current != nullptr) {
        if (current == &value) {
            return false;
        }
        current = current->next;
    }

    if (size == 0 || index > size - 1) {
        return false;
    } else if (size == 1) {
	    delete first;
	    first = &value;
	    first->next = nullptr;
	    first->prev = nullptr;
	    last = first;
    } else if (index == 0) {
        DroneRecord* start = first->next;

        delete start->prev;
	    first = &value;

        start->prev = first;
        first->next = start;
        first->prev = nullptr;

        return true;
    } else if (index == size - 1) {
        DroneRecord* end = last->prev;

        delete end->next;
        last = &value;

        end->next = last;
        last->next = nullptr;
        last->prev = end;

        return true;
	} else {
        DroneRecord* current = first; // initialize end pointer
        unsigned int i = 0;
        while (current != nullptr) { // iterate until NULL
            if (i == index) {
                DroneRecord* pre = current->prev;
                DroneRecord* post = current->next;

                post->prev = &value;
                pre->next = &value;

                value.next = post;
                value.prev = pre;

                delete current;
                return true;
            }
            current = current->next;
            i++;
        }
	}
}

bool DronesManager::reverse_list() {
    if (size == 0) {
	    return false;
	} else if (size == 1) {
	    return true;
	} else {
        DroneRecord* temp = nullptr;
        DroneRecord* current = first;
        last = first;

        //swap next and prev for all DroneRecords
        while (current !=  nullptr)
        {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        first = temp->prev;

        return true;
	}
}

bool DronesManagerSorted::is_sorted_asc() const {
	DroneRecord* current = first->next;
	while (current != nullptr) {
	    if (current->droneID < current->prev->droneID) {
	        return false;
	    }
	    current = current->next;
	}
    return true;
}

bool DronesManagerSorted::is_sorted_desc() const {
    DroneRecord* current = first->next;
    while (current != nullptr) {
        if (current->droneID > current->prev->droneID) {
            return false;
        }
        current = current->next;
    }
    return true;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    //check if value is unique
    DroneRecord* current = first;
    while (current != nullptr) {
        if (current == &val) {
            return false;
        }
        current = current->next;
    }

    if (size == 0) {
        first = &val;
        first->next = nullptr;
        first->prev = nullptr;
        last = first;
        size++;
        return true;
    } else if (size == 1) {
        if (val.droneID > first->droneID) {
            DroneRecord* end = last;

            end->next = &val;
            val.next = nullptr;
            val.prev = end;
            last = &val;
        } else {
            DroneRecord* start = first;

            start->prev = &val;
            val.next = start;
            val.prev = nullptr;
            first = &val;
        }
        size++;
        return true;
    } else {
        current = first;
        //set current to node after insertion point
        while (current->droneID < val.droneID && current->next != nullptr) {
            current = current->next;
        }

        if (current->prev == nullptr) {
            DroneRecord* start = first->next;

            delete start->prev;
            first = &val;

            start->prev = first;
            first->next = start;
            first->prev = nullptr;
            size++;
            return true;
        } else if (current->next == nullptr) {
            DroneRecord* end = last->prev;

            delete end->next;
            last = &val;

            end->next = last;
            last->prev = end;
            last->next = nullptr;
            size++;
            return true;
        }

        current = current->prev;
        DroneRecord* new_rec = &val;

        new_rec->next = current->next;
        current->next = new_rec;
        new_rec->prev = current;

        if (new_rec->next != nullptr)
            new_rec->next->prev = new_rec;

        if (new_rec->next == nullptr) {
            last = new_rec;
        }
        size++;
        return true;
    }

}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    //check if value is unique
    DroneRecord* current = first;
    while (current != nullptr) {
        if (current == &val) {
            return false;
        }
        current = current->next;
    }

    if (size == 0) {
        first = &val;
        first->next = nullptr;
        first->prev = nullptr;
        last = first;
        size++;
        return true;
    } else if (size == 1) {
        if (val.droneID < first->droneID) {
            DroneRecord* end = last;

            end->next = &val;
            val.next = nullptr;
            val.prev = end;
            last = &val;
        } else {
            DroneRecord* start = first;

            start->prev = &val;
            val.next = start;
            val.prev = nullptr;
            first = &val;
        }
        size++;
        return true;
    } else {
        current = first;
        //set current to node after insertion point
        while (current->droneID > val.droneID && current ->next != nullptr) {
            current = current->next;
        }

        if (current->prev == nullptr) {
            DroneRecord* start = first->next;

            delete start->prev;
            first = &val;

            start->prev = first;
            first->next = start;
            first->prev = nullptr;
            size++;
            return true;
        } else if (current->next == nullptr) {
            DroneRecord* end = last->prev;

            delete end->next;
            last = &val;

            end->next = last;
            last->prev = end;
            last->next = nullptr;
            size++;
            return true;
        }

        current = current->prev;
        DroneRecord* new_rec = &val;

        new_rec->next = current->next;
        current->next = new_rec;
        new_rec->prev = current;

        if (new_rec->next != nullptr)
            new_rec->next->prev = new_rec;

        if (new_rec->next == nullptr) {
            last = new_rec;
        }
        size++;
        return true;
    }
}

void DronesManagerSorted::sort_asc() {
    for (int i = 0; i < size; ++i) {
        DroneRecord* current = first;
        for (int j = 0; j < (size - 1); ++j) {
            if (current->droneID > current->next->droneID) {
                unsigned int tempID = current->droneID;
                current->droneID = current->next->droneID;
                current->next->droneID = tempID;
            }
            current = current->next;
        }
    }
}
    
void DronesManagerSorted::sort_desc() {
    for (int i = 0; i < size; ++i) {
        DroneRecord* current = first;
        for (int j = 0; j < (size - 1); ++j) {
            if (current->droneID < current->next->droneID) {
                unsigned int tempID = current->droneID;
                current->droneID = current->next->droneID;
                current->next->droneID = tempID;
            }
            current = current->next;
        }
    }
}
