//
// Martin Ethier, ID: 20660931
//
#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "drones_manager.hpp"
#include <ctime>

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// new empty list is valid
    bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == nullptr)
		ASSERT_TRUE(manager.last == nullptr)
	    return true;
    }

	// insert_front() and insert_back() on zero-element list
    bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != nullptr && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != nullptr && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == nullptr && manager1.last->next == nullptr)
		ASSERT_TRUE(manager2.first->prev == nullptr && manager2.last->next == nullptr)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
	    return true;
    }

	// select() and search() work properly
    bool test3() {
	    DronesManager manager;
	    manager.insert_back(DronesManager::DroneRecord(22));
        manager.insert_front(DronesManager::DroneRecord(475));
        manager.insert_back(DronesManager::DroneRecord(12));
        manager.insert_front(DronesManager::DroneRecord(9265));

        ASSERT_TRUE(manager.search(DronesManager::DroneRecord(22)) == 2 && manager.select(2) == DronesManager::DroneRecord(22))
        ASSERT_TRUE(manager.search(DronesManager::DroneRecord(475)) == 1 && manager.select(1) == DronesManager::DroneRecord(475))
        ASSERT_TRUE(manager.search(DronesManager::DroneRecord(12)) == 3 && manager.select(3) == DronesManager::DroneRecord(12))
        ASSERT_TRUE(manager.search(DronesManager::DroneRecord(9265)) == 0 && manager.select(0) == DronesManager::DroneRecord(9265))
        return true;
    }
    
    // remove_front() and remove_back() on one-element list
    bool test4() {
        DronesManager manager;
        manager.insert_back(DronesManager::DroneRecord(1));
        ASSERT_TRUE(manager.get_size() == 1)

        manager.remove_front();
        ASSERT_TRUE(manager.get_size() == 0)
        ASSERT_TRUE(manager.empty() == true)
        ASSERT_TRUE(manager.first == nullptr)
        ASSERT_TRUE(manager.last == nullptr)

        manager.insert_front(DronesManager::DroneRecord(533));
        ASSERT_TRUE(manager.get_size() == 1)

        manager.remove_back();
        ASSERT_TRUE(manager.get_size() == 0)
        ASSERT_TRUE(manager.empty() == true)
        ASSERT_TRUE(manager.first == nullptr)
        ASSERT_TRUE(manager.last == nullptr)
	    return true;
    }
    
    // replace() and reverse_list() work properly
    bool test5() {
        DronesManager manager;
        manager.insert_front(DronesManager::DroneRecord(203));
        manager.replace(0,DronesManager::DroneRecord(304));
        ASSERT_TRUE(manager.first->prev == nullptr && manager.first->next == nullptr)
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(304))

        manager.insert_back(DronesManager::DroneRecord(5));
        manager.insert_front(DronesManager::DroneRecord(84));
        manager.replace(1,DronesManager::DroneRecord(34));
        manager.replace(2,DronesManager::DroneRecord(1023));
        ASSERT_TRUE(manager.first->prev == nullptr && manager.last->next == nullptr)
        ASSERT_TRUE(manager.select(1) == DronesManager::DroneRecord(34) && manager.select(2) == DronesManager::DroneRecord(1023))

        DronesManager reverse_manager;
        reverse_manager.insert_front(DronesManager::DroneRecord(1023));
        reverse_manager.insert_back(DronesManager::DroneRecord(34));
        reverse_manager.insert_back(DronesManager::DroneRecord(84));
        manager.reverse_list();
        ASSERT_TRUE(manager.select(0) == reverse_manager.select(0))
        ASSERT_TRUE(manager.select(1) == reverse_manager.select(1))
        ASSERT_TRUE(manager.select(2) == reverse_manager.select(2))

	    return true;
    }
    
    // insert_front() keeps moving elements forward
    bool test6() {
        DronesManager manager;
        manager.insert_front(DronesManager::DroneRecord(20));
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(20))

        manager.insert_front(DronesManager::DroneRecord(13));
        ASSERT_TRUE(manager.select(1) == DronesManager::DroneRecord(20))

        manager.insert_front(DronesManager::DroneRecord(54));
        ASSERT_TRUE(manager.select(2) == DronesManager::DroneRecord(20))

        manager.insert_front(DronesManager::DroneRecord(2));
        ASSERT_TRUE(manager.select(3) == DronesManager::DroneRecord(20))

        manager.insert_front(DronesManager::DroneRecord(90));
        ASSERT_TRUE(manager.select(4) == DronesManager::DroneRecord(20))

        manager.insert_front(DronesManager::DroneRecord(5));
        ASSERT_TRUE(manager.select(5) == DronesManager::DroneRecord(20))
	    return true;
    }
    
    // inserting at different positions in the list
    bool test7() {
	    DronesManager manager;
	    manager.insert(DronesManager::DroneRecord(23),0);
        manager.insert(DronesManager::DroneRecord(5),0);
        manager.insert(DronesManager::DroneRecord(76),1);
        manager.insert(DronesManager::DroneRecord(930),3);
        manager.insert(DronesManager::DroneRecord(37),0);
        manager.insert(DronesManager::DroneRecord(102),3);
        manager.insert(DronesManager::DroneRecord(366),2);
        manager.insert(DronesManager::DroneRecord(9),7);

        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(37))
        ASSERT_TRUE(manager.select(1) == DronesManager::DroneRecord(5))
        ASSERT_TRUE(manager.select(2) == DronesManager::DroneRecord(366))
        ASSERT_TRUE(manager.select(3) == DronesManager::DroneRecord(76))
        ASSERT_TRUE(manager.select(4) == DronesManager::DroneRecord(102))
        ASSERT_TRUE(manager.select(5) == DronesManager::DroneRecord(23))
        ASSERT_TRUE(manager.select(6) == DronesManager::DroneRecord(930))
        ASSERT_TRUE(manager.select(7) == DronesManager::DroneRecord(9))
 	    return true;
    }
    
    // try to remove too many elements, then add a few elements
    bool test8() {
        DronesManager manager;
        manager.insert_back(DronesManager::DroneRecord(145));
        manager.remove(0);
        ASSERT_TRUE(manager.size == 0)
        manager.remove(0);
        manager.remove_front();
        manager.remove_back();

        manager.insert_front(DronesManager::DroneRecord(34));
        ASSERT_TRUE(manager.size == 1 && manager.select(0) == DronesManager::DroneRecord(34))
	    return true;
    }
    
 	// lots of inserts and deletes, some of them invalid
	bool test9() {
        srand(time(NULL)); //seed for random number
	    DronesManager manager;
	    for (int i = 0; i < 20; i++) {
            manager.insert_back(DronesManager::DroneRecord(rand()%999 + 1));
        }
        manager.insert(DronesManager::DroneRecord(948),manager.size + 1);
		return true;
	}    
	    	
	// inserts into an unsorted list, then sort the list
	bool test10() {
	    DronesManagerSorted manager;
	    manager.insert_front(DronesManager::DroneRecord(34));
	    manager.insert_front(DronesManager::DroneRecord(764));
	    manager.insert_front(DronesManager::DroneRecord(12));
        manager.insert_front(DronesManager::DroneRecord(90));
        manager.insert_front(DronesManager::DroneRecord(4));
        manager.insert_front(DronesManager::DroneRecord(235));
        manager.insert_front(DronesManager::DroneRecord(655));
        manager.insert_front(DronesManager::DroneRecord(58));

        manager.sort_asc();

        ASSERT_TRUE(manager.is_sorted_asc() == true)
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(4))
        ASSERT_TRUE(manager.select(1) == DronesManager::DroneRecord(12))
        ASSERT_TRUE(manager.select(2) == DronesManager::DroneRecord(34))
        ASSERT_TRUE(manager.select(3) == DronesManager::DroneRecord(58))
        ASSERT_TRUE(manager.select(4) == DronesManager::DroneRecord(90))
        ASSERT_TRUE(manager.select(5) == DronesManager::DroneRecord(235))
        ASSERT_TRUE(manager.select(6) == DronesManager::DroneRecord(655))
        ASSERT_TRUE(manager.select(7) == DronesManager::DroneRecord(764))

	    return true;
	}  
	
	// insert into sorted manager in ascending order
	bool test11() {
        DronesManagerSorted manager;

        manager.insert_sorted_asc(DronesManager::DroneRecord(345));
        manager.insert_sorted_asc(DronesManager::DroneRecord(55));
        manager.insert_sorted_asc(DronesManager::DroneRecord(98));
        manager.insert_sorted_asc(DronesManager::DroneRecord(1936));
        manager.insert_sorted_asc(DronesManager::DroneRecord(6));

        ASSERT_TRUE(manager.is_sorted_asc() == true)

	    return true;
	}
	
	//insert and remove into sorted manager in descending order
	bool test12() {
        DronesManagerSorted manager;

        manager.insert_sorted_desc(DronesManager::DroneRecord(345));
        manager.insert_sorted_desc(DronesManager::DroneRecord(55));
        manager.insert_sorted_desc(DronesManager::DroneRecord(98));
        manager.insert_sorted_desc(DronesManager::DroneRecord(1936));
        manager.insert_sorted_desc(DronesManager::DroneRecord(6));

        ASSERT_TRUE(manager.is_sorted_desc() == true)

        return true;
	}  
};


#endif
