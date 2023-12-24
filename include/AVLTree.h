#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <queue>
#include "TreeNode.h"

enum BalanceStatus {
	LEFT_SKEWED = -1,														// Node is left-skewed
	RIGHT_SKEWED = 1,														// Node is right-skewed
	BALANCED = 0															// Node is balanced
};

template <class T> class AVLTree											// BEGIN: AVL Tree BASE template
{
private:																	// ---------------------------------------------------------------- 

	// Private class properties and methods
	Node<T>* root;															// Property: root node

	// AVL tree maintenance methods
	void update_height(Node<T>*& inpRoot);									// Update the height of a node
	void rotate_left(Node<T>*& inpRoot);									// Rotate the tree to the left
	void rotate_right(Node<T>*& inpRoot);									// Rotate the tree to the right
	void update_balance(Node<T>*& inpRoot);									// Update the balance factor of a node

public:																		// ----------------------------------------------------------------- 

	// Public class properties and methods
	AVLTree();																// Default constructor
	AVLTree(const Node<T>&);												// Parameterized constructor
	AVLTree(const AVLTree<T>&);												// Copy constructor
	~AVLTree();																// Destructor

	Node<T>* get_root() const;												// Get the root of the tree
	int height_tree() const;												// Get the height of the tree
	int count() const;														// Count the number of nodes in the tree
	T get_max() const;														// Get the maximum key in the tree
	T get_min() const;														// Get the minimum key in the tree

	void insert(const T&);													// Insert a key into the tree
	void remove(const T&);													// Remove a key from the tree
	void clear_tree();														// Clear the entire tree

	bool is_empty() const;													// Check if the tree is empty
	bool search(const T&) const;											// Search for a key in the tree

	void display() const;													// Display the contents of the AVLTree

	void in_order_traversal(std::ostream&) const;							// Depth-First Traversal: in-order traversal
	void pre_order_traversal(std::ostream&) const;							// Depth-First Traversal: pre-order traversal
	void post_order_traversal(std::ostream&) const;							// Depth-First Traversal: post-order traversal
	void level_order_traversal(std::ostream&) const;						// Breadth-First Traversal: lever-order traversal

	AVLTree<T>& operator=(const AVLTree<T>&);								// Assignment operator

	template <class U>
	friend std::ostream& operator<<(std::ostream&, const AVLTree<U>&);		// Output stream operator

private:																	// ------------------------------------------------------------- 
	// Private class properties and methods (helper)

	Node<T>* min_node(Node<T>* inpRoot) const;								// Find the node with the minimum key in the AVL tree rooted at inpRoot.
	Node<T>* max_node(Node<T>* inpRoot) const;								// Find the node with the maximum key in the AVL tree rooted at inpRoot.
	int count(Node<T>* inpRoot) const;										// Count the number of nodes in the AVL tree rooted at inpRoot.
	int get_height(Node<T>* inpRoot) const;									// Get the height of the AVL tree rooted at inpRoot.

	void insert(Node<T>*& inpRoot, const T& inpKey);						// Insert a key into the AVL tree rooted at inpRoot.
	void remove(Node<T>*& inpRoot, const T& inpKey);						// Remove a key from the AVL tree rooted at inpRoot.

	Node<T>* copy_node(Node<T>* inpNode);									// Create a deep copy of the subtree rooted at inpNode.
	void clear_tree(Node<T>*& inpRoot);										// Recursively clear the AVL tree rooted at inpRoot.

	bool search(Node<T>*, const T&) const;									// Search for a key in the AVL tree rooted at inpRoot.
	
	void in_order_traversal(Node<T>*, std::ostream&) const;					// Traverse and print nodes in in-order sequence.
	void pre_order_traversal(Node<T>*, std::ostream&) const;				// Traverse and print nodes in pre-order sequence.
	void post_order_traversal(Node<T>*, std::ostream&) const;				// Traverse and print nodes in post-order sequence.
	void level_order_traversal(Node<T>*, std::ostream&) const;				// Traverse and print nodes in level-order sequence.

};																			// END Class

#endif // !AVLTREE_H