#ifndef HASHTABLE_H
#define HASHTABLE_H
#define ull unsigned long long

#include <iostream>
#include <fstream>
#include <string>
#include "HashNode.h"
#include "AVLTree.h"
#include "TreeNode.h"


#define A (std::sqrt(5.00) - 1.00) / 2.00									// The golden ratio (used in the hash function)


template <class T> class HashTable : public HashNode<T>						// Class template HashTable
{
private:																	// ------------------------------------------------
	// Private class properties and methods
	typedef HashNode<T>* HashEntry;

	HashEntry* table;														// Array of entries (buckets) for the HashTable
	int size;																// Size of Array
	std::ofstream output;													// Output file stream for logging

	virtual int hash_function(const T& key) const;							// Hash function to calculate the index based on the key

public:																		// ------------------------------------------------
	// Public class properties and methods

	HashTable(const int&, const std::string&);								// Constructor with specified size and output file name

	~HashTable();															// Destructor to free allocated memory

	HashEntry* get_table() const;											// Get the array of entries (buckets) in the HashMap

	int get_size() const;													// Get the size of the HashTable

	void insert(const T& key);												// Insert a key into the HashTable

	void save_result_insert_list(const T*, const int&);						// Insert multiple keys from an array into the HashMap ad

	void search(const T& key);												// Search for a key in the HashTable

	void save_result_search_list(const T*, const int&);						// Search for multiple keys from an array in the HashTable

	void print_table(const std::string&);									// Print HashMap to file

	void display();															// Display the contents of the HashTable

	template <class U>
	friend std::ostream& operator<<(std::ostream&, const HashTable<U>&);	// Friend function to overload the stream insertion operator for output
};

#endif // !HASHTABLE_H