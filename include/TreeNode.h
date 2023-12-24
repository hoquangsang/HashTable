#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
#include <iomanip>
#include <string>

enum HeightStatus {
    h_leaf = 1,                                                             // The height of a leaf node is 1.
    h_null = 0,                                                             // The height of a null node is 0.
};

template <class T> class Node                                               // TreeNode BASE template
{
private:                                                                    // -------------------------------------------
    // Private class properties and methods

    T key;                                                                  // Key value
    int height;                                                             // Height: balance value
    Node<T>* left;                                                          // Left pointer link
    Node<T>* right;                                                         // Right pointer link

    int get_height(Node<T>* nodePtr) const;                                 // Private method: get height of a node

public:                                                                     // -------------------------------------------
    // Public class properties and methods

    // Constructors
    Node();                                                                 // Default constructor
    Node(const T& inpKey);                                                  // Parameterized constructor
    Node(const T& inpKey, Node<T>* leftPtr, Node<T>* rightPtr);             // Parameterized constructor
    Node(const Node<T>& inpNode);                                           // Copy constructor

    // Getter methods
    T get_key() const;                                                      // Get the key value
    int get_height() const;                                                 // Get the height of the node
    int get_balance() const;                                                // Get the balance factor of the node
    Node<T>*& get_leftptr();                                                // Get the left pointer of the node
    Node<T>*& get_rightptr();                                               // Get the right pointer of the node

    // Setter methods
    void set_key(const T& inpKey);                                          // Set the key value
    void set_leftptr(Node<T>* nodePtr);                                     // Set the left pointer of the node
    void set_rightptr(Node<T>* nodePtr);                                    // Set the right pointer of the node

    // Update
    void update_height();                                                   // Update the height of the node

    // Assignment operator
    Node<T>& operator=(const Node<T>&);                                     // Assignment operator

    // ostream operator
    template <class U>
    friend std::ostream& operator<<(std::ostream&, const Node<U>&);         // Output stream operator
};


#endif //!TREENODE_H