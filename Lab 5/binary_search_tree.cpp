//
// Martin Ethier, ID: 20660931
// Extra helper functions implemented:
// getNodeDepth, clear, getMax, recursiveRemove
//
#include <iostream>
#include <queue>
#include "binary_search_tree.hpp"

using namespace std;

BinarySearchTree::Node::Node( int new_val ) {
    val = new_val;
    left = right = nullptr;
}

void clear(BinarySearchTree::Node* node) {
    BinarySearchTree::Node* n = node;
    if (n->left != nullptr) {
        clear(n->left);
    }
    if (n->right != nullptr) {
        clear(n->right);
    }
    delete n;
    node = NULL;
}


BinarySearchTree::BinarySearchTree() {
	size_ = 0;
	root_ = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    if (root_) {
        clear(root_);
        size_ = 0;
    }
}

unsigned int BinarySearchTree::getNodeDepth( Node* n ) const {
	// Returns depth from node to furthest leaf (to be used in 'depth' function)
    // From the description, it sounds like we want it to return the depth from the root
    // to the node but this has no use for the other functions.
    if (n == nullptr) {
        return 0;
	} else {
        // Depth of each child
        unsigned int leftDepth = getNodeDepth(n->left);
        unsigned int rightDepth = getNodeDepth(n->right);
        // Return largest value
        return leftDepth > rightDepth ? leftDepth + 1: rightDepth + 1;
    }
}

unsigned int BinarySearchTree::size() const {
	return size_;
}

int BinarySearchTree::max() const {
	Node* cur = root_;

	while (cur->right) {
		cur = cur->right;
	}

	return cur->val;
}

int BinarySearchTree::min() const {
	Node* cur = root_;

	while (cur->left) {
		cur = cur->left;
	}

	return cur->val;
}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_) - 1;
}

void BinarySearchTree::print() const {
    // print using level order traversal
    // If no nodes, return an empty string.
    if (root_ == NULL) {
        return;
    }
    cout << "\nLevel order: ";
    queue<BinarySearchTree::Node*> node_queue;
    node_queue.push(root_);
    while (!node_queue.empty()) {
        BinarySearchTree::Node* cur_node = node_queue.front();
        node_queue.pop();
        cout << cur_node->val << " ";
        if (cur_node->left != NULL) {
            node_queue.push(cur_node->left);
        }
        if (cur_node->right != NULL) {
            node_queue.push(cur_node->right);
        }
    }
}

bool BinarySearchTree::exists( int val ) const {
	Node* cur = root_;

	while (cur) {
		if (cur->val == val) return true;
		else if (val < cur->val) cur = cur->left;
		else cur = cur->right;
	}

	return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert( int val ) {
    Node** cur = &root_;
    while (*cur) {
        if (val < (*cur)->val) {
            cur = &(*cur)->left;
        } else {
            cur = &(*cur)->right;
        }
    }
    *cur = new Node(val);
    ++size_;
    return true;
}

BinarySearchTree::Node* getMax(BinarySearchTree::Node* node) {
    BinarySearchTree::Node* cur = node;

    while (cur->right) {
        cur = cur->right;
    }

    return cur;
}

BinarySearchTree::Node* recursiveRemove(BinarySearchTree::Node* root, int val)
{
    if (!root) {
        return root;
    } else if (val > root->val) {
        root->right = recursiveRemove(root->right, val);
    } else if (val < root->val) {
        root->left = recursiveRemove(root->left, val);
    } else {
        if (!root->right && !root->left) {
            delete root;
            root = nullptr;
        } else if (!root->left) {
            BinarySearchTree::Node* temp = root;

            root = root->right;
            delete temp;
        } else if (!root->right) {
            BinarySearchTree::Node* temp = root;

            root = root->left;
            delete temp;
        } else {
            BinarySearchTree::Node* temp = getMax(root->left);

            root->val = temp->val;
            root->left = recursiveRemove(root->left, temp->val);
        }
    }
    return root;
}

bool BinarySearchTree::remove( int val ) {
    if (!exists(val)) {
        return false;
    }
    root_ = recursiveRemove(root_, val);

    size_--;
    return true;
}
