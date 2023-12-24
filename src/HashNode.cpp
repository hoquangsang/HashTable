#include "HashNode.h"

// Explicit instantiations
// ---------------------------------------------------------
#pragma region
template class HashNode<int>;
template class HashNode<float>;
template class HashNode<double>;
template class HashNode<char>;
template class HashNode<wchar_t>;
template class HashNode<bool>;
template class HashNode<std::string>;
// template class HashNode<size_t>;
#pragma endregion
// ---------------------------------------------------------


// Constructor & destructor
// ---------------------------------------------------------
#pragma region
// Default constructor
template <class T> HashNode<T>::HashNode() {
    // BEGIN: Default constructor for HashNode

    // 1. Set the key to the default value for int.
    this->key = T();

    // 2. Create a new AVL tree for handling collisions.
    this->collisionList = new AVLTree<T>();

    // END
}

// Parameterized constructor with a key
template <class T> HashNode<T>::HashNode(const T& inpKey) {
    // BEGIN: Parameterized constructor with a key for HashNode

    // 1. Set the key to the specified input key.
    this->key = inpKey;

    // 2. Create a new AVL tree for handling collisions.
    this->collisionList = new AVLTree<T>();

    // END: Parameterized constructor with a key for HashNode
}

// Parameterized constructor with a key and existing AVL tree
template <class T> HashNode<T>::HashNode(const T& inpKey, const AVLTree<T>& inpTree) {
    // BEGIN: Parameterized constructor with a key and existing AVL tree for HashNode

    // 1. Set the key to the specified input key.
    this->key = inpKey;

    // 2. Create a new AVL tree for handling collisions with the specified existing tree.
    this->collisionList = new AVLTree<T>(inpTree);

    // END
}

// Destructor
template <class T> HashNode<T>::~HashNode() {
    // BEGIN: Destructor for HashNode

    // 1. Check if the collisionList is not nullptr.
    if (this->collisionList != nullptr) {

        // 2. Clear the AVL tree (collisionList) to release memory.
        this->collisionList->clear_tree();

        // 3. Delete the AVL tree (collisionList).
        delete this->collisionList;

        // 4. Set the collisionList pointer to nullptr.
        this->collisionList = nullptr;
    }

    // END
}

#pragma endregion
// ---------------------------------------------------------


// Public methods
// ---------------------------------------------------------
#pragma region
template <class T> T HashNode<T>::get_key() const {
    // BEGIN: Get the key of the HashNode

    // Return the key value of the HashNode.
    return this->key;

    // END
}

template <class T> AVLTree<T>* HashNode<T>::get_listptr() const {
    // BEGIN: Get the pointer to the collision list of the HashNode

    // Return the pointer to the collision list (AVL tree) of the HashNode.
    return this->collisionList;

    // END
}
template <class T> void HashNode<T>::set_key(const T& inpKey) {
    // BEGIN: Set the key of the HashNode

    this->key = inpKey;

    // END
}

template <class T> void HashNode<T>::set_listptr(const AVLTree<T>& inpList) {
    // BEGIN: Set the collision list pointer of the HashNode

    // 1. Clear existing collision list if it exists
    if (this->collisionList != nullptr) {
        this->collisionList->clear_tree();
        delete this->collisionList;
        this->collisionList = nullptr;
    }

    // 2. Create a new collision list by copying the input AVL tree
    this->collisionList = new AVLTree<T>(inpList);

    // END
}

template <class T> int HashNode<T>::count_collisions() const {
    // BEGIN: Count the number of collisions in the collision list of the HashNode

    // Use the count method of the collision list (AVL tree) to get the number of collisions.
    return this->collisionList->count();

    // END
}

template <class T> bool HashNode<T>::no_collision() const {
    // BEGIN: Check if the HashNode has collisions

    // Return true if the collision list is not empty, indicating collisions.
    return this->collisionList->is_empty();

    // END
}

template <class T> void HashNode<T>::insert(const T& inpKey) {
    // BEGIN: Insert a key into the collision list of the HashNode

    // Use the insert method of the collision list (AVL tree) to handle collisions.
    this->collisionList->insert(inpKey);

    // END
}

template <class T> bool HashNode<T>::search(const T& inpKey) const {
    // BEGIN: Search for a key in the HashNode and its collision list

    // 1. Check if the key of the HashNode matches the input key.
    if (this->key == inpKey) {
        return true;
    }
    else {
        // 2. If not, search for the key in the collision list (AVL tree).
        return this->collisionList->search(inpKey);
    }

    // END
}

template <class T> void HashNode<T>::display() const {
    // BEGIN: Display the key and collision list of the HashNode

    // 1. Display the key with padding and formatting.
    std::cout << std::setw(3) << std::setfill('0') << key << " ";

    // 2. Display the collision list using the << operator.
    std::cout << *this->collisionList;

    // END
}

template <class T> HashNode<T>& HashNode<T>::operator=(const HashNode<T>& inpOther) {
    // BEGIN: Assignment operator to copy the content of another HashNode

    // 1. Check for self-assignment.
    if (this != &inpOther) {
        // 2. Clear the existing collision list of the current HashNode.
        this->collisionList->clear_tree();
        delete this->collisionList;
        this->collisionList = nullptr;

        // 3. Copy the key from the other HashNode.
        this->key = inpOther.get_key();

        // 4. Copy the collision list (AVL tree) from the other HashNode.
        this->collisionList = new AVLTree<T>(*inpOther.collisionList);
    }

    // 5. Return a reference to the modified HashNode.
    return *this;

    // END
}
#pragma endregion
// ---------------------------------------------------------


// Friend
// ---------------------------------------------------------
#pragma region
template <class T> std::ostream& operator<<(std::ostream& os, const HashNode<T>& inpNode) {
    // BEGIN: Friend function to display the HashNode content using the << operator

    // 1. Display the key with padding and formatting.
    os << std::setw(3) << std::setfill('0') << inpNode.get_key() << " ";

    // 2. Display the collision list using the << operator.
    os << *inpNode.get_listptr();

    // 3. Return the modified output stream.
    return os;

    // END
}
template std::ostream& operator<<(std::ostream&, const HashNode<int>&);
template std::ostream& operator<<(std::ostream&, const HashNode<float>&);
template std::ostream& operator<<(std::ostream&, const HashNode<double>&);
template std::ostream& operator<<(std::ostream&, const HashNode<char>&);
template std::ostream& operator<<(std::ostream&, const HashNode<wchar_t>&);
template std::ostream& operator<<(std::ostream&, const HashNode<bool>&);
template std::ostream& operator<<(std::ostream&, const HashNode<std::string>&);
#pragma endregion
// ---------------------------------------------------------