#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP
#include <string>
#include <iostream>
using namespace std;

// Implementation of Heap ADT as a Priority Queue of Task Items
class PriorityQueue { 
public:
  // Visible externally as PriorityQueue::TaskItem
  struct TaskItem {
	int priority; // normal values are greater than zero
	string description; // task description
	TaskItem(int new_priority, string new_desc) : 
		priority(new_priority), description(new_desc) {}
  };

private:
  friend class PriorityQueueTest;

  // Sequential representation of the priority queue.
  TaskItem** heap_;

  // Total number of elements that the priority queue can store.
  unsigned int capacity_;
  
  // Current number of elements in the priority queue.
  unsigned int size_;
  
public:
  // Constructor initializes heap to an array of (capacity + 1) size, 
  // so that there are at most capacity elements in the priority queue. 
  PriorityQueue(unsigned int capacity);
  // Destructor of the class PriorityQueue. 
  // It deallocates the memory space allocated for the priority queue. 
  ~PriorityQueue();
  
  // Returns the number of elements in the priority queue.
  unsigned int size() const;
  // Returns true if the priority queue is empty, and false otherwise.
  bool empty() const;
  // Returns true if the priority queue is full, and false otherwise.
  bool full() const;
  // Prints the contents of the priority queue. Format is not specified.
  void print() const;
  // Returns the max element of the priority queue, but does not remove it. 
  // If the priority queue is empty, it returns (-1, "NULL").
  TaskItem max() const;

  
  // Inserts the given value into the priority queue. 
  // Returns true if successful, and false otherwise.
  // Priority queue does not change in capacity.
  bool enqueue(TaskItem val);
  // Removes the top element with the maximum value (priority) and rearranges
  // the resulting heap. Returns true if successful, and false otherwise.
  // Priority queue does not change in capacity.
  bool dequeue();  
};
#endif 
