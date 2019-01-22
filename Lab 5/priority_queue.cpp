//
// Martin Ethier, ID: 20660931
//

#include "priority_queue.hpp"

using namespace std;
PriorityQueue::PriorityQueue(unsigned int capacity) {
	heap_ = new TaskItem*[capacity+1];
	size_ = 0;
	capacity_ = capacity;
}

PriorityQueue::~PriorityQueue() {
	for (int i = 1; i < size_; i ++) {
		delete heap_[i];
	}
	delete [] heap_;
	//heap_ = NULL;
}

unsigned int PriorityQueue::size() const {
	return size_;
}

bool PriorityQueue::empty() const {
	return size_ == 0;
}

bool PriorityQueue::full() const {
	return size_ >= capacity_;
}

void PriorityQueue::print() const {
	cout << "Printing heap...\n\n";
	for (int i = 1; i < size_ + 1; i ++) {
		cout << heap_[i]->priority << " ";
	}
	cout << endl;
}

PriorityQueue::TaskItem PriorityQueue::max() const {
	return empty() ? TaskItem(-1, "NULL") : *heap_[1];
}

bool PriorityQueue::enqueue( TaskItem val ) {
	if (size_ == capacity_) {
		return false;
	}

	if (size_ == 0) {
		heap_[1] = new TaskItem(val.priority, val.description);
	} else {
		int i = size_ + 1;
		heap_[i] = new TaskItem(val.priority, val.description); //assign item to end of tree
		while (i > 1 && heap_[i/2]->priority < heap_[i]->priority) {
			//swap i with its parent node
			TaskItem *temp = heap_[i];
			heap_[i] = heap_[i/2];
			heap_[i/2] = temp;
			i /= 2; //move to parent node
		}
	}
	size_ ++;
	return true;
}

bool PriorityQueue::dequeue() {
	if (size_ == 0) {
		return false;
	}

	if (size_ == 1) {
		heap_[1] = nullptr;
		size_ --;
	} else {
		//swap first and last nodes
		heap_[1]->priority = heap_[size_]->priority;
		heap_[1]->description = heap_[size_]->description;
        size_ --;

        int i = 1;
		while (i <= size_/2) {
		    //swap i with its largest child node or non null node
			if (heap_[2*i+1] == NULL) {
                TaskItem *temp = heap_[i];
                heap_[i] = heap_[2 * i];
                heap_[2 * i] = temp;
				delete heap_[2*i];
                i *= 2;
            } else if (heap_[2*i] == NULL) {
                TaskItem *temp = heap_[i];
                heap_[i] = heap_[2*i+1];
                heap_[2*i+1] = temp;
				delete heap_[2*i+1];
                i = 2*i + 1;
            } else if (heap_[2*i]->priority > heap_[2*i+1]->priority) {
                TaskItem *temp = heap_[i];
                heap_[i] = heap_[2 * i];
                heap_[2 * i] = temp;
				delete heap_[2*i];
                i *= 2;
			} else if (heap_[2*i]->priority < heap_[2*i+1]->priority) {
				TaskItem *temp = heap_[i];
				heap_[i] = heap_[2*i+1];
				heap_[2*i+1] = temp;
				delete heap_[2*i+1];
				i = 2*i + 1;
			}
		}
	}

	return true;
}
