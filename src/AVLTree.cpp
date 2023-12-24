#include "AVLTree.h"

// Explicit instantiations
// ---------------------------------------------------------
#pragma region
template class AVLTree<int>;
template class AVLTree<float>;
template class AVLTree<double>;
template class AVLTree<char>;
template class AVLTree<wchar_t>;
template class AVLTree<bool>;
template class AVLTree<std::string>;
// template class Node<size_t>;
#pragma endregion
// ---------------------------------------------------------


// Private methods: Maintain AVL
// ---------------------------------------------------------
#pragma region
template <class T> void AVLTree<T>::update_height(Node<T>*& inpRoot) {
	// BEGIN: Implement update height

	// Check if the node is null, nothing to update
	if (inpRoot == nullptr) return;

	// Update the height of the current node using its children's heights
	inpRoot->update_height();

	// END
}

template <class T> void AVLTree<T>::rotate_left(Node<T>*& inpRoot) {
	// BEGIN: Implement rotate left
	if (inpRoot == nullptr) return;

	// 1. Set a temporary pointer to the right child of this node.
	Node<T>* tempPtr = inpRoot->get_rightptr();

	// 2. Set the right child of this node to the left child of the temporary pointer.
	inpRoot->set_rightptr(tempPtr->get_leftptr());

	// 3. Set the left child of the temporary pointer to this node.
	tempPtr->set_leftptr(inpRoot);

	// 4. Update the heights of this node and the temporary pointer.
	update_height(inpRoot);
	update_height(tempPtr);

	// 5. Set this node to the temporary pointer, making it the new root after rotation.
	inpRoot = tempPtr;
	// END
}

template <class T> void AVLTree<T>::rotate_right(Node<T>*& inpRoot) {
	// BEGIN: Implement rotate right
	if (inpRoot == nullptr) return;

	// 1. Set a temporary pointer to the left child of this node.
	Node<T>* tempPtr = inpRoot->get_leftptr();

	// 2. Set the left child of this node to the right child of the temporary pointer.
	inpRoot->set_leftptr(tempPtr->get_rightptr());

	// 3. Set the right child of the temporary pointer to this node.
	tempPtr->set_rightptr(inpRoot);

	// 4. Update the heights of this node and the temporary pointer.
	update_height(inpRoot);
	update_height(tempPtr);

	// 5. Set this node to the temporary pointer, making it the new root after rotation.
	inpRoot = tempPtr;
	// END

}

template <class T> void AVLTree<T>::update_balance(Node<T>*& inpRoot) {
	// BEGIN: Rebalance the tree

	if (inpRoot == nullptr) return;

	// 1. Get the balance factor
	int balValue = inpRoot->get_balance();

	// 2. Check if Left-skewed case
	if (balValue < LEFT_SKEWED) {
		// 2.1 Get the left child
		Node<T>*& leftSubTree = inpRoot->get_leftptr();

		// 2.2 Check the balance factor of the left subtree (left - right)
		if (leftSubTree->get_balance() > BALANCED) {	
			rotate_left(leftSubTree);
		}

		// 2.3 Perform right rotation for left-skewed case (left - left)
		rotate_right(inpRoot);

		// 2.4 Recursively update balance for the right subtree
		update_balance(inpRoot->get_rightptr());
	}
	// 3. Check if Right-skewed case
	else if (balValue > RIGHT_SKEWED) {
		// 3.1 Get the right child
		Node<T>*& rightSubTree = inpRoot->get_rightptr();

		// 3.2 Check the balance factor of the right subtree (right - left)
		if (rightSubTree->get_balance() < BALANCED) {
			rotate_right(rightSubTree);
		}

		// 3.3 Perform left rotation for right-skewed case (right - right)
		rotate_left(inpRoot);
		
		// 3.4 Recursively update balance for the left subtree
		update_balance(inpRoot->get_leftptr());
	}
	// 4. If not
	else {
		// Update the height if the tree is balanced
		update_height(inpRoot);
	}
	// END
}
#pragma endregion
// ---------------------------------------------------------


// Constructor & destructor
// ---------------------------------------------------------
#pragma region
template <class T> AVLTree<T>::AVLTree() {
	// BEGIN: Default constructor

	// 1.  Initialize the root pointer to nullptr
	this->root = nullptr;

	// END
}

template <class T> AVLTree<T>::AVLTree(const Node<T>& inpNode) {
	// BEGIN: Constructor with a node

	// 1. Initialize the root pointer to nullptr
	this->root = new Node<T>(inpNode);
		
	// END
}

template <class T> AVLTree<T>::AVLTree(const AVLTree<T>& inpTree) {
	// BEGIN: Copy constructor

	// Recursive: Create a new Node by copying the root of the input tree
	this->root = new Node<T>(*inpTree.root);

	// END
}

template <class T> AVLTree<T>::~AVLTree() {
	// BEGIN: Destructor

	this->clear_tree();

	// END
}
#pragma endregion
// ---------------------------------------------------------


// Public properties & methods
// ---------------------------------------------------------
#pragma region

// getter methods
template <class T> Node<T>* AVLTree<T>::get_root() const {
	// BEGIN: Get the root of the tree
	return this->root;
	// END
}

template <class T> int AVLTree<T>::height_tree() const {
	// BEGIN: Get the height of the tree
	return get_height(this->root);
	// END
}

template <class T> T AVLTree<T>::get_max() const {
	// BEGIN: Get the maximum key in the tree
	if (is_empty()) return T();

	// Use helper function to find the node with the maximum key
	return max_node(this->root)->get_key();
	// END
}

template <class T> T AVLTree<T>::get_min() const {
	// BEGIN: Get the minimum key in the tree
	if (is_empty()) return T();
	return min_node(this->root)->get_key();
	// END
}

template <class T> int AVLTree<T>::count() const {
	// BEGIN: Get the number of nodes in the tree
	return count(this->root);
	// END
}

// build tree: methods
template <class T> void AVLTree<T>::insert(const T& inpKey) {
	// BEGIN: Insert a key into the tree
	insert(this->root, inpKey);
	// END
}

template <class T> void AVLTree<T>::remove(const T& inpKey) {
	// BEGIN: Remove a key from the tree
	remove(this->root, inpKey);
	// END
}

template <class T> void AVLTree<T>::clear_tree() {
	// BEGIN: Clear the entire tree
	clear_tree(this->root);
	// END
}

// check
template <class T> bool AVLTree<T>::is_empty() const {
	// BEGIN: Check if the tree is empty
	return (this->root == nullptr);
	// END
}

template <class T> bool AVLTree<T>::search(const T& inpKey) const {
	// BEGIN: Search for a key in the tree
	return search(this->root, inpKey);
	// END
}

// display
template <class T> void AVLTree<T>::display() const {
	// BEGIN: Display the tree using pre-order traversal
	std::cout << *this;
	// END
}

// traversal
template <class T> void AVLTree<T>::in_order_traversal(std::ostream& os) const {
	// BEGIN: In-order traversal
	in_order_traversal(this->root, os);
	// END
}

template <class T> void AVLTree<T>::pre_order_traversal(std::ostream& os) const {
	// BEGIN: Pre-order traversal
	pre_order_traversal(this->root, os);
	// END
}

template <class T> void AVLTree<T>::post_order_traversal(std::ostream& os) const {
	// BEGIN: Post-order traversal
	post_order_traversal(this->root, os);
	// END
}

template <class T> void AVLTree<T>::level_order_traversal(std::ostream& os) const {
	// BEGIN: Level-order traversal
	level_order_traversal(this->root, os);
	// END
}

// assign operator:
template <class T>  AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& inpTree) {
	// BEGIN: Assignment operator to copy the tree
	if (this != &inpTree) {
		this->clear_tree();
		this->root = copy_node(inpTree.get_root());
	}
	return *this;
	// END
}

#pragma endregion
// ---------------------------------------------------------


// friend template class AVLTree
// ---------------------------------------------------------
#pragma region
template <class T> std::ostream& operator<<(std::ostream& os, const AVLTree<T>& inpTree) {
	// BEGIN: Friend function to output the tree using pre-order traversal
	inpTree.pre_order_traversal(os);
	return os;
	// END
}

template std::ostream& operator<<(std::ostream&, const AVLTree<int>&);
template std::ostream& operator<<(std::ostream&, const AVLTree<float>&);
template std::ostream& operator<<(std::ostream&, const AVLTree<double>&);
template std::ostream& operator<<(std::ostream&, const AVLTree<char>&);
template std::ostream& operator<<(std::ostream&, const AVLTree<wchar_t>&);
template std::ostream& operator<<(std::ostream&, const AVLTree<bool>&);
template std::ostream& operator<<(std::ostream&, const AVLTree<std::string>&);
// ---------------------------------------------------------
//
#pragma endregion
// ---------------------------------------------------------


// Private methods: build tree
// ---------------------------------------------------------
#pragma region
// traversal
template <class T> void AVLTree<T>::in_order_traversal(Node<T>* inpRoot, std::ostream& os) const {
	// BEGIN: In-order traversal

	// 1. Check the base case: If the current node is nullptr, terminate the function.
	if (inpRoot == nullptr) return;

	// 2. Recursively call for the left child node:
	in_order_traversal(inpRoot->get_leftptr(), os);

	// 3. Output the value of the current node to the stream:
	os << *inpRoot << " ";

	// 4. Recursively call for the right child node:
	in_order_traversal(inpRoot->get_rightptr(), os);

	// END
}

template <class T> void AVLTree<T>::pre_order_traversal(Node<T>* inpRoot, std::ostream& os) const {
	// BEGIN: Pre-order traversal

	// 1. Check the base case: If the current node is nullptr, terminate the function.
	if (inpRoot == nullptr) return;

	// 2. Output the value of the current node to the stream:
	os << *inpRoot << " ";

	// 3. Recursively call for the left child node:
	pre_order_traversal(inpRoot->get_leftptr(), os);

	// 4. Recursively call for the right child node:
	pre_order_traversal(inpRoot->get_rightptr(), os);

	// END
}

template <class T> void AVLTree<T>::post_order_traversal(Node<T>* inpRoot, std::ostream& os) const {
	// BEGIN: Post-order traversal

	// 1. Check the base case: If the current node is nullptr, terminate the function.
	if (inpRoot == nullptr) return;

	// 2. Recursively call for the left child node:
	post_order_traversal(inpRoot->get_leftptr(), os);

	// 3. Recursively call for the right child node:
	post_order_traversal(inpRoot->get_rightptr(), os);

	// 4. Output the value of the current node to the stream:
	os << *inpRoot << " ";

	// END
}

template <class T> void AVLTree<T>::level_order_traversal(Node<T>* inpRoot, std::ostream& os) const {
	// BEGIN: Level-order traversal

	// 1. Check the base case: If the current node is nullptr, terminate the function.
	if (inpRoot == nullptr) return;

	// 2. Create a queue to keep track of nodes at each level.
	std::queue<Node<T>*> queue;
	queue.push(inpRoot);

	// 3. Process nodes level by level using the queue.
	while (!queue.empty()) {
		// 4. Get the front node from the queue.
		Node<T>* cur_node = queue.front();
		// 5. Output the value of the current node to the stream.
		os << *cur_node << " ";
		// 6. Remove the front node from the queue.
		queue.pop();

		// 7. Enqueue the left child if it exists.
		if (cur_node->get_leftptr()) {
			queue.push(cur_node->get_leftptr());
		}

		// 8. Enqueue the right child if it exists.
		if (cur_node->get_rightptr()) {
			queue.push(cur_node->get_rightptr());
		}
	}

	// END
}

// Search
template <class T> bool AVLTree<T>::search(Node<T>* inpRoot, const T& inpKey) const {
	// BEGIN: Search for a key in the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, the key is not found.
	if (inpRoot == nullptr) return false;

	// 2. Compare the target key with the key of the current node.
	else if (inpKey < inpRoot->get_key()) {
		// 3. If the target key is less than the current node's key, recursively search in the left subtree.
		return search(inpRoot->get_leftptr(), inpKey);
	}
	else if (inpKey > inpRoot->get_key()) {
		// 4. If the target key is greater than the current node's key, recursively search in the right subtree.
		return search(inpRoot->get_rightptr(), inpKey);
	}

	// 5. If the target key is equal to the current node's key, the key is found.
	return true;

	// END
}

// getter
template <class T> Node<T>* AVLTree<T>::min_node(Node<T>* inpRoot) const {
	// BEGIN: Find the node with the minimum key in the AVL tree rooted at inpRoot

	// 1. Initialize the minimum node as the root of the subtree.
	Node<T>* minNode = inpRoot;

	// 2. Traverse the left child pointers until the leftmost node is reached.
	while (minNode->get_leftptr()) {
		minNode = minNode->get_leftptr();
	}

	// 3. Return the node with the minimum key.
	return minNode;

	// END
}

template <class T> Node<T>* AVLTree<T>::max_node(Node<T>* inpRoot) const {
	// BEGIN: Find the node with the maximum key in the AVL tree rooted at inpRoot

	// 1. Initialize the maximum node as the root of the subtree.
	Node<T>* maxNode = inpRoot;

	// 2. Traverse the right child pointers until the rightmost node is reached.
	while (maxNode->get_rightptr()) {
		maxNode = maxNode->get_rightptr();
	}

	// 3. Return the node with the maximum key.
	return maxNode;

	// END
}

template <class T> int AVLTree<T>::count(Node<T>* inpRoot) const {
	// BEGIN: Count the number of nodes in the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, return 0.
	if (inpRoot == nullptr) return 0;

	// 2. Recursively count the nodes in the left and right subtrees, and add 1 for the current node.
	return 1 + count(inpRoot->get_leftptr()) + count(inpRoot->get_rightptr());

	// END
}

template <class T> int AVLTree<T>::get_height(Node<T>* inpRoot) const {
	// BEGIN: Get the height of the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, return 0.
	if (inpRoot == nullptr) return 0;

	// 2. Return the height of the current node.
	return inpRoot->get_height();

	// END
}

// insert & remove
template <class T> void AVLTree<T>::insert(Node<T>*& inpRoot, const T& inpKey) {
	// BEGIN: Insert a key into the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, create a new node with the key.
	if (inpRoot == nullptr) {
		inpRoot = new Node<T>(inpKey);
		return;
	}
	else if (inpKey < inpRoot->get_key()) {
		// 2. If the key is less than the current node's key, recursively insert into the left subtree.
		insert(inpRoot->get_leftptr(), inpKey);
	}
	else if (inpKey > inpRoot->get_key()) {
		// 3. If the key is greater than the current node's key, recursively insert into the right subtree.
		insert(inpRoot->get_rightptr(), inpKey);
	}
	else {
		// 4. If the key is equal to the current node's key, do nothing (no duplicates allowed).
		return;
	}

	// 5. Update the balance factor and perform rotations if necessary.
	update_balance(inpRoot);

	// END
}

template <class T> void AVLTree<T>::remove(Node<T>*& inpRoot, const T& inpKey) {
	// BEGIN: Remove a key from the AVL tree rooted at inpRoot

	// 1. Check the base case: If the current node is nullptr, the key does not exist.
	if (inpRoot == nullptr) {
		return;
	}
	// 2. If the key is less than the current node's key, recursively remove from the left subtree.
	else if (inpKey < inpRoot->get_key()) {
		remove(inpRoot->get_leftptr(), inpKey);
	}
	// 3. If the key is greater than the current node's key, recursively remove from the right subtree.
	else if (inpKey > inpRoot->get_key()) {
		remove(inpRoot->get_rightptr(), inpKey);
	}
	// 4. If not
	else {
		// 4.1 Handle cases where the node to be removed has one or no child.
		if (inpRoot->get_leftptr() == nullptr) {
			Node<T>* reNode = inpRoot;
			inpRoot = inpRoot->get_rightptr();
			delete reNode;
		}
		else if (inpRoot->get_rightptr() == nullptr) {
			Node<T>* reNode = inpRoot;
			inpRoot = inpRoot->get_leftptr();
			delete reNode;
		}
		// 4.2 Handle case where the node to be removed has two children.
		else {
			Node<T>* reNode = min_node(inpRoot->get_rightptr());
			inpRoot->set_key(reNode->get_key());
			remove(inpRoot->get_rightptr(), reNode->get_key());
		}
	}

	// 5. Update the balance factor and perform rotations if necessary.
	update_balance(inpRoot);

	// END
}

template <class T> Node<T>* AVLTree<T>::copy_node(Node<T>* inpNode) {
	// BEGIN: Create a deep copy of the subtree rooted at inpNode

	// 1. Check the base case: If the current node is nullptr, return nullptr.
	if (inpNode != nullptr) {
		// 1.1 Create a new node with the key of the current node.
		Node<T>* newRoot = new Node<T>(inpNode->get_key());

		// 1.2 Recursively copy the left and right subtrees.
		Node<T>* leftPtr = copy_node(inpNode->get_leftptr());
		Node<T>* rightPtr = copy_node(inpNode->get_rightptr());

		// 1.3 Set the left and right child pointers of the new node.
		newRoot->set_leftptr(leftPtr);
		newRoot->set_rightptr(rightPtr);

		// 1.4 Return the new node.
		return newRoot;
	}

	// 2. If the current node is nullptr, return nullptr.
	return nullptr;

	// END
}

template <class T> void AVLTree<T>::clear_tree(Node<T>*& inpRoot) {
	// BEGIN: Recursively clear the AVL tree rooted at inpRoot

	// Check if the current node is not nullptr.
	if (inpRoot != nullptr) {
		// 1. Recursively clear the left and right subtrees.
		Node<T>*& leftPtr = inpRoot->get_leftptr();
		Node<T>*& rightPtr = inpRoot->get_rightptr();
		clear_tree(leftPtr);
		clear_tree(rightPtr);

		// 2. Delete the current node and set it to nullptr.
		delete inpRoot;
		inpRoot = nullptr;
	}

	// END
}

#pragma endregion
// ---------------------------------------------------------