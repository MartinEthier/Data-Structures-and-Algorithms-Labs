#ifndef A3_TESTS_HPP
#define A3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include <algorithm>
#include <sstream>
#include <queue>

#include "priority_queue.hpp"
#include "binary_search_tree.hpp"

class PriorityQueueTest {
public:
	// New queue is valid
  bool test1() {
    PriorityQueue q(5);
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

	// Enqueue one item and then dequeue it
  bool test2() {
    PriorityQueue q(2);
    ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(10,"Test Task")) );
    ASSERT_TRUE( !q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 1 );
    ASSERT_TRUE( q.max().priority == 10 );

	ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

	// Enqueue too many
  bool test3()
  {
    PriorityQueue q(3);
    ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(5,"Test Task")) );
    ASSERT_TRUE( q.max().priority == 5 );
    ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(3,"Test Task")) );
    ASSERT_TRUE( q.max().priority == 5 );
    ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(4,"Test Task")) );
    ASSERT_TRUE( q.max().priority == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE( !q.enqueue(PriorityQueue::TaskItem(7,"Test Task")) );
    ASSERT_TRUE( q.max().priority == 5 );
    ASSERT_TRUE( q.full() );
    return true;
  }
  
  // Enqueue too many then dequeue too many
bool test4()
{
    PriorityQueue q(3);
    ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(5,"Test Task")) );
    ASSERT_TRUE( q.max().priority == 5 );
    ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(3,"Test Task")) );
    ASSERT_TRUE( q.max().priority == 5 );
    ASSERT_TRUE( q.enqueue(PriorityQueue::TaskItem(4,"Test Task")) );
    ASSERT_TRUE( q.max().priority == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE( !q.enqueue(PriorityQueue::TaskItem(7,"Test Task")) );
    ASSERT_TRUE( q.max().priority == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.max().priority == 4 );
    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.max().priority == 3 );
    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );

    ASSERT_TRUE( !q.dequeue() );
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    return true;
}
};

class BinarySearchTreeTest {
public:
bool insert_nodes(BinarySearchTree &tree, int *in, int nin)
{
  for(int i = 0; i < nin; i++) {
    ASSERT_TRUE(tree.insert(in[i]));
  }
  return true;
}

  // Traverse the tree in level-order to check if it was constructed properly
  // Output is as follows: "val1 val2 ... valN"
  // where vali is the value of node i, using level-order traversal
  std::string level_order(BinarySearchTree::Node* root)
  {
    // If no nodes, return an empty string.
    if (root == NULL) {
      return "";
    }
    
    std::stringstream ss;
    std::queue<BinarySearchTree::Node*> node_queue;
    node_queue.push(root);
    while (!node_queue.empty()) {
      BinarySearchTree::Node* cur_node = node_queue.front();
      node_queue.pop();
      ss << cur_node->val << " ";
      if (cur_node->left != NULL) {
        node_queue.push(cur_node->left);
      }
      if (cur_node->right != NULL) {
        node_queue.push(cur_node->right);
      }
    }
    
    std::string level_order_str = ss.str();
    // There is a trailing space at the end of the string; return everything
    // before this.
    return level_order_str.substr(0, level_order_str.size() - 1);
  }

	//  New tree is valid
bool test1()
{
    // We expect an empty tree at construction.
    std::string expected_tree_level_order = "";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.root_ == NULL);
    ASSERT_TRUE(bst.size_ == 0 && bst.size() == 0);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
}

// Test a tree with one node
bool test2()
{
    // We expect a single root node with value "5" after everything.
    std::string expected_tree_level_order = "5";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(5));
    ASSERT_TRUE(!bst.remove(4));
    ASSERT_TRUE(bst.exists(5));
    ASSERT_TRUE(bst.max() == bst.min() && bst.max() == 5);
    ASSERT_TRUE(bst.size() == 1);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
}

// Insert, remove, and size on linear list formation with three elements
bool test3()
{
    // We expect a 2-node tree at the end of this function -- root node 10 and
    // a child node with value 8.
    std::string expected_tree_level_order = "10 8";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(8));
    ASSERT_TRUE(bst.size() == 2);
    ASSERT_TRUE(bst.insert(6));
    ASSERT_TRUE(bst.size() == 3);

    ASSERT_TRUE(bst.remove(6));
    ASSERT_TRUE(bst.size() == 2);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
}

// Test removal of a node with one child
bool test4()
{
  std::string expected_tree = "3 2 6";
  
  BinarySearchTree bst;
  ASSERT_TRUE(bst.insert(3));
  ASSERT_TRUE(bst.insert(7));
  ASSERT_TRUE(bst.insert(6));
  ASSERT_TRUE(bst.insert(2));
  
  ASSERT_TRUE(bst.remove(7));
  ASSERT_TRUE(!bst.exists(7));
  ASSERT_TRUE(level_order(bst.root_).compare(expected_tree) == 0)
  return true;
}

// Insert multiple elements and remove till nothing remains
bool test5()
{
  std::string expected_tree = "";
  
  BinarySearchTree bst;  
  int in[] = {8, 3, 10, 15};
  
  ASSERT_TRUE(insert_nodes(bst, in, 4));
  ASSERT_TRUE(!bst.remove(9));
  ASSERT_TRUE(bst.remove(8));
  ASSERT_TRUE(bst.max() == 15);
  ASSERT_TRUE(bst.remove(15));
  ASSERT_TRUE(bst.max() == 10);
  ASSERT_TRUE(bst.min() == 3);
  ASSERT_TRUE(bst.remove(10));  
  ASSERT_TRUE(bst.remove(3));
  ASSERT_TRUE(bst.root_== NULL);
  ASSERT_TRUE(level_order(bst.root_).compare(expected_tree) == 0)
  return true;
}
 
 // Test removal of root node when both children of root have two children
bool test6()
{
  std::string expected_tree1 = "6 3 10 1 9 15";
  std::string expected_tree2 = "9 3 10 1 6 15";
  
  BinarySearchTree bst;
  int in[] = {8, 3, 10, 1, 6, 9, 15};
  
  ASSERT_TRUE(insert_nodes(bst, in, 7));
  ASSERT_TRUE(!bst.remove(12));
  ASSERT_TRUE(bst.remove(8));
  ASSERT_TRUE(level_order(bst.root_).compare(expected_tree1) == 0 ||
              level_order(bst.root_).compare(expected_tree2) == 0)
  return true;
}

// Test depth with many inserts & some removes.
bool test7()
{
  std::string expected_tree = "0 -5 10 -2 1 -4 -1";
  
  BinarySearchTree bst;
  ASSERT_TRUE(bst.insert(0));
  ASSERT_TRUE(bst.depth() == 0)
  ASSERT_TRUE(bst.insert(10));
  ASSERT_TRUE(bst.depth() == 1)
  ASSERT_TRUE(bst.insert(-5));
  ASSERT_TRUE(bst.depth() == 1)
  ASSERT_TRUE(bst.insert(-2));
  ASSERT_TRUE(bst.depth() == 2);
  ASSERT_TRUE(bst.insert(-4));
  ASSERT_TRUE(bst.depth() == 3);
  ASSERT_TRUE(bst.insert(-1));
  ASSERT_TRUE(bst.depth() == 3);
  ASSERT_TRUE(bst.insert(1));
  ASSERT_TRUE(bst.depth() == 3);
  ASSERT_TRUE(level_order(bst.root_).compare(expected_tree) == 0)
  return true;
}

	// Lots of inserts and removes
bool test8() {
  // In this case, it is the expected tree before removing all nodes.
  std::string expected_tree = "8 2 9 1 7 4 3 5 6";
  
  BinarySearchTree bst;
  int in[] = {8, 2, 7, 4, 5, 3, 1, 9, 6};
  int nin = 9;
  ASSERT_TRUE(insert_nodes(bst, in, nin));
  ASSERT_TRUE(level_order(bst.root_).compare(expected_tree) == 0)
  for(int i = 0; i<nin; ++i)
  {
    ASSERT_TRUE(bst.remove(in[i]));
  }
  ASSERT_TRUE(!bst.remove(in[0]));
  return true;
}
};
#endif
