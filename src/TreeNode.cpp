#include "TreeNode.h"

// Explicit instantiations
// ---------------------------------------------------------
// Refs: https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file/495056#495056
#pragma region
template class Node<int>;
template class Node<float>;
template class Node<double>;
template class Node<char>;
template class Node<wchar_t>;
template class Node<bool>;
template class Node<std::string>;
#pragma endregion
// ---------------------------------------------------------


// Private methods
// ---------------------------------------------------------
#pragma region
template <class T> int Node<T>::get_height(Node<T>* nodePtr) const {
	// the height of a null node is h_null (0)
	if (nodePtr == nullptr) return h_null;

	// get the height of node
	return nodePtr->get_height();
}
#pragma endregion
// ---------------------------------------------------------


// Constructor
// ---------------------------------------------------------
#pragma region
template <class T> Node<T>::Node() {
	// BEGIN: Implement the default constructor

	// 1. Set the key to the default value of int (0)
	this->key = T();

	// 2. Initialize the left pointer to nullptr
	this->left = nullptr;

	// 3. Initialize the right pointer to nullptr
	this->right = nullptr;

	// 4. Set the height to a predefined null height value (assuming h_null is an enum)
	this->height = h_leaf;

	// END
}

template <class T> Node<T>::Node(const T& inpKey) {
	// BEGIN: Implement the parameterized constructor

	// 1. Set the key to the input key value
	this->key = inpKey;

	// 2. Initialize the left pointer to nullptr
	this->left = nullptr;

	// 3. Initialize the right pointer to nullptr
	this->right = nullptr;

	// 4. Set the height to a predefined leaf height value (assuming h_null is an enum)
	this->height = h_leaf;

	// END
}

template <class T> Node<T>::Node(const T& inpKey, Node<T>* leftPtr, Node<T>* rightPtr) {
	// BEGIN: Implement the parameterized constructor

	// 1. Set the key to the input key value
	this->key = inpKey;

	// 2. Initialize the left pointer to nullptr
	this->left = leftPtr;

	// 3. Initialize the right pointer to nullptr
	this->right = rightPtr;

	// 4. Calculate the height based on the heights of left and right subtrees
	this->height = 1 + std::max(get_height(this->left), get_height(this->right));
	// END
}

template <class T> Node<T>::Node(const Node<T>& inpNode) {
	// BEGIN: Implement the parameterized constructor

	// 1. Copy the key from inpNode to the current node
	this->key = inpNode.key;

	// 2. Initialize left and right pointers to nullptr
	this->left = nullptr;
	this->right = nullptr;

	// 3. If inpNode has a left child, recursively copy the left subtree
	if (inpNode.left != nullptr) {
		// recursive: create a new Node by copying the left subtree of inpNode
		this->left = new Node<T>(*inpNode.left);
	}

	// 4. If inpNode has a right child, recursively copy the right subtree
	if (inpNode.right != nullptr) {
		// recursive: create a new Node by copying the right subtree of inpNode
		this->right = new Node<T>(*inpNode.right);
	}

	// 5. Copy the height from inpNode to the current node
	this->height = inpNode.height;

	// END
}
#pragma endregion
// ---------------------------------------------------------


// public methods
// ---------------------------------------------------------
#pragma region
// getter methods
template <class T> T Node<T>::get_key() const {
	// BEGIN: Implement get this key value
	return this->key;
	// END
}

template <class T> int Node<T>::get_height() const {
	// BEGIN: Implement get this height
	return this->height;
	// END
}

template <class T> int Node<T>::get_balance() const {
	// BEGIN: Implement get balance factor

	// 1. Calculate the heights of the left and right subtrees
	int left_height = (this->left == nullptr) ? 0 : this->left->height;
	int right_height = (this->right == nullptr) ? 0 : this->right->height;

	// 2. Return the balance factor (difference between the heights of the right and left subtrees)
	return right_height - left_height;
	// END
}

template <class T> Node<T>*& Node<T>::get_leftptr() {
	// BEGIN: Implement get left pointer
	return this->left;
	// END
}

template <class T> Node<T>*& Node<T>::get_rightptr() {
	// BEGIN: Implement get right pointer
	return this->right;
	// END
}

// setter methods
template <class T> void Node<T>::set_key(const T& inpKey) {
	// BEGIN: Implement set key
	this->key = inpKey;
	// END
}

template <class T> void Node<T>::set_leftptr(Node<T>* nodePtr) {
	// BEGIN: Implement set left ptr
	this->left = nodePtr;
	// END
}

template <class T> void Node<T>::set_rightptr(Node<T>* nodePtr) {
	// BEGIN: Implement set right ptr
	this->right = nodePtr;
	// END
}

template <class T> void Node<T>::update_height() {
	// BEGIN: Implement update height
	this->height = 1 + std::max(get_height(this->left), get_height(this->right));
	// END
}

// asignment operator
template <class T>
Node<T>& Node<T>::operator=(const Node<T>& inpNode) {
	if (this != &inpNode) {
		this->key = inpNode.key;
		this->left = inpNode.left;
		this->right = inpNode.right;
		this->height = inpNode.height;
	}
	return *this;
}

#pragma endregion
// ---------------------------------------------------------


// friend
// ---------------------------------------------------------
#pragma region
// friend ostream opearator
template <class T> std::ostream& operator<<(std::ostream& os, const Node<T>& inpNode) {
	// BEGIN: Implement ostream 
	os << " -> " << std::setw(3) << std::setfill('0') << inpNode.get_key();
	return os;
	// END
}

template std::ostream& operator<<(std::ostream&, const Node<int>&);
template std::ostream& operator<<(std::ostream&, const Node<float>&);
template std::ostream& operator<<(std::ostream&, const Node<double>&);
template std::ostream& operator<<(std::ostream&, const Node<char>&);
template std::ostream& operator<<(std::ostream&, const Node<wchar_t>&);
template std::ostream& operator<<(std::ostream&, const Node<bool>&);
template std::ostream& operator<<(std::ostream&, const Node<std::string>&);

#pragma endregion
// ---------------------------------------------------------