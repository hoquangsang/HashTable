#ifndef HASHNODE_H
#define HASHNODE_H

#include <iostream>	
#include "AVLTree.h"

// class template HashNode
template <class T> class HashNode											//
{
private:
	// Private class properties and methods
	T key;											// Key of the hash node
	AVLTree<T>* collisionList;						// AVL tree to handle collisions

public:
	// Public class properties and methods
	HashNode();																// Default constructor
	HashNode(const T&);														// Constructor with a key
	HashNode(const T&, const AVLTree<T>&);									// Constructor with a key and existing AVL tree
	~HashNode();															// Destructor

	T get_key() const;														// Get the key of the hash node
	AVLTree<T>* get_listptr() const;										// Get a pointer to the collision list (AVL tree)
	
	void set_key(const T&);													// Set the key
	void set_listptr(const AVLTree<T>&);									// Set the collision list

	bool no_collision() const;												// Check if the hash node has collisions (non-empty collision list)
	int count_collisions() const;											// Count the number of collisions in the collision list
	
	void insert(const T&);													// Insert a key into the collision list (AVL tree)
	bool search(const T&) const;											// Search for a key in the collision list
	
	void display() const;													// Display the collision list

	HashNode<T>& operator=(const HashNode<T>&);								// Assignment operator to copy the content of another HashNode

	template <class U>
	friend std::ostream& operator<<(std::ostream&, const HashNode<U>&);		// Friend function for stream output
};

#endif // !HASHNODE_H