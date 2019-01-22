//
// Martin Ethier, 20660931
//

#include "records_manager_test.h"
#include "records_manager.h"

bool RecordsManagerTest::test1() {
    cout << "Test 1: Testing regular insertion and removal of records...\n\nInserting Records...\n";
    RecordsManager manager;
    manager.insertRecord(25433,1344,"Martin Donat Ethier","182 Spruce Court","Jan 9th 1998");
    manager.insertRecord(8236,1344,"Martin Donat Ethier","182 Spruce Court","Jan 9th 1998");
    manager.insertRecord(1864,11234,"Martin Donat Ethier","182 Spruce Court","Jan 9th 1998");
    manager.insertRecord(8236,9912,"Martin Donat Ethier","182 Spruce Court","Jan 9th 1998");

    manager.print();
    cout << "Removing records...\n";
    manager.removeRecord(25433,1344);
    manager.removeRecord(8236,1344);
    manager.removeRecord(1864,11234);
    manager.removeRecord(8236,9912);
    manager.print();
    cout << "\n\n";
    return true;

}

bool RecordsManagerTest::test2() {
    cout << "Test 2: Testing manager expansion and shrinking...\n\n";
    RecordsManager manager;

    cout << "Initial capacity of manager: " << manager.capacity << "\nInserting records to beyond capacity...\n";
    srand(time(NULL));
    int cap = manager.capacity;
    while (manager.size <= cap) {
        manager.insertRecord(rand()%999999 + 1,rand()%999999 + 1,"","","");
    }

    cout << "Current capacity of manager: " << manager.capacity << "\nInserting records to beyond capacity...\n";
    cap = manager.capacity;
    while (manager.size <= cap) {
        manager.insertRecord(rand()%999999 + 1,rand()%999999 + 1,"","","");
    }

    cout << "Current capacity of manager: " << manager.capacity << "\nRemoving records to a quarter of capacity...\n";
    cap = manager.capacity;
    while (manager.size >= cap/4) {
        manager.removeRecord(manager.data[0]->getCatID(),manager.data[0]->getPatID());
    }

    cout << "Current capacity of manager: " << manager.capacity << "\n\n\n";

    return true;
}

bool RecordsManagerTest::test3() {
    cout << "Test 3: Testing special cases...\n\n";
    RecordsManager manager;

    cout << "Inserting a record...\n\n";
    manager.insertRecord(2345,927,"Martin Donat Ethier","182 Spruce Court","Jan 9th 1998");
    manager.print();
    cout << "Attempting to insert a record with the same IDs...\n";
    manager.insertRecord(2345,927,"Igor Ivkovic","200 University Ave W","Jan 1st 2000");
    cout << "\nAttempting to remove non-existent record...\n";
    manager.removeRecord(244,5244);
    cout << "Removing added record...\n";
    manager.removeRecord(2345,927);
    manager.print();
    cout << "\nAttempting to remove record from empty manager...\n";
    manager.removeRecord(245,53);

    return true;
}

bool RecordsManagerTest::test4() {

}

bool RecordsManagerTest::test5() {

}

bool RecordsManagerTest::test6() {

}

bool RecordsManagerTest::test7() {

}

bool RecordsManagerTest::test8() {

}

bool RecordsManagerTest::test9() {

}

bool RecordsManagerTest::test10() {

}
