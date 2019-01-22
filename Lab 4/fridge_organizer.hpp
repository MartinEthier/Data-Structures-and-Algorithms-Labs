//
// Martin Ethier
// ID: 20660931
//
#ifndef STACKS_HPP
#define STACKS_HPP
using namespace std;

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;
#define ASSERT_NULL(T) if (!(T)) return false;
#define ASSERT_NOT_NULL(T) if ((T)) return false;

class FridgeOrganizerTest;

class FridgeOrganizer {
	struct MealPortion { // internal class that allows storage of meal portions
		string name; // name of meal portion
		string expiry; // expiry of meal portion
		MealPortion(string n_name, string n_expiry) : name(n_name), expiry(n_expiry) {}
		void print() { cout << "| ELEMENT: " << name << ", " << expiry << " |" << endl; }
	};

	list<stack<MealPortion*>*> stacks; // a doubly-linked list of stack pointers
	unsigned int stack_number; // maximum number of stacks
	unsigned int usable_stacks; // leave one stack empty for shuffling
	unsigned int stack_capacity; // maximum stack capacity
	
	friend FridgeOrganizerTest;

public:
	// parametric constructor for FridgeOrganizer
	FridgeOrganizer(unsigned int n_stack_number, unsigned int n_stack_capacity);
	
	// destructor for FridgeOrganizer
	~FridgeOrganizer();
	
	// display all meal stacks in the fridge
	void print_stacks();

	// return number of portions in the fridge
	int number_of_portions();
	
	// add a new meal portion to existing portions if there is space
	// insert the portion into the first empty stack from the back
	bool add_meal_portion(string n_name, string n_expiry);

	// remove the meal from the fridge based on LIFO principle
	// if the fridge is empty, return ("EMPTY", "N/A")
	MealPortion remove_meal_portion();
	
	// find the meal in the fridge with earliest expiry date value
	// ensure that the method does not disrupt other functionality
	// assume that valid expiry will be expressed as YY-MM-DD
	// if the fridge is empty, return ("EMPTY", "N/A")
	MealPortion find_meal_portion_by_expiry();
};

class FridgeOrganizerTest {	
	// test FridgeOrganizer constructor and basic item insertion
	bool test1();
	
	// test stack growth and shrinking with LIFO removal
	bool test2();
	
	// test find meal portion by earliest expiry date
	bool test3();
	
public:	
	void runTests();
};
#endif
