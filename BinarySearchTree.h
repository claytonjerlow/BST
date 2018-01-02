#ifndef __BINARYSEARCHTREE__
#define __BINARYSEARCHTREE__

#include <iostream>

//namespace keeps Tree, node, and iterator classes unique to the namespace
namespace pic10b{
    /**
     Class functions as a binary search tree.
     */
    class Tree{
    private:
        /**
         Nested class acts as a wrapper for double values that the Tree class stores. Has pointers to parent, right, and left nodes.
         */
        class node;
        
        node* root; //the root of the Tree
        std::size_t sz; //the number of elements in the tree
        
        /**
         Recursive function goes to the bottom of each branch and deletes nodes moving upwards.
         
         @param n the root of the tree to be deleted
         */
        void deleteTree(node* n);
        
        /**
         Recursive function aids in transfering data from one Tree to another during copying, ensuring the new Tree has the same structure.
         
         @param n the root of the tree to be copied
         */
        void traverseInsert(node* n);
    public:
        
        /**
         Nested class acts as a way to bounce from node to node in a Tree. Has a pointer to its current node and a pointer to the Tree it works in.
         */
        class iterator; //must be public for operator!=
        
        /**
         Default constructor sets root to null and sz to 0.
         */
        Tree();
        
        /**
         Destructor calls deleteTree recursive function to delete all nodes and setting sz to 0.
         */
        ~Tree();
        
        /**
         Copy constructor calls traverseInsert function to transfer data from an existing Tree to a new Tree while maintaining structure.
         
         @param rhs the Tree to be copied
         */
        Tree(const Tree& rhs);
        
        /**
         Move constructor makes a new Tree by stealing the root and sz of a given Tree.
         
         @param rhs the Tree whose data is to be stolen
         */
        Tree(Tree&& rhs);
        
        /**
         Function swaps the roots and sizes of two given Trees. Friend because it needs access to the root and size values.
         
         @param one the first Tree to be swapped
         @param another the second Tree to be swapped with first
         */
        friend void swap(Tree& one, Tree& another);
        
        /**
         Assignment operator (both copy and move) swaps the roots and sizes of this Tree and a given Tree.
         
         @param rhs the Tree to be assigned to this Tree
         @return this Tree with the new root and sz from rhs
         */
        Tree& operator=(Tree rhs);
        
        /**
         Function inserts a double into the Tree by constructing a node from the value and passing that node to the insertNode function.
         
         @param val the number to be added to the Tree
         */
        void insert(double val);
        
        /**
         Function erases a node from the Tree at the provided iterator.
         
         @param itr the location of the node to be erased
         */
        void erase(iterator itr);
        
        /**
         Function provides an iterator of the node with the lowest value (furthest left) in the Tree.
         
         @return the iterator at the beginning
         */
        iterator begin() const;
        
        /**
         Function provides the iterator past the end of the Tree.
         
         @return iterator with nullptr node
         */
        iterator end() const;
        
        /**
        Function provides the size of the Tree.
         
         @return sz the size of the Tree
        */
        std::size_t size() const;
        
        /**
         Function searches through the Tree for a value and returns the iterator to the node with that value if it is found.
         
         @param val the number to be searched for
         @return the iterator to the node with the found value or nullptr (end()) if val is not found in the Tree
         */
        iterator find(double val);
    };
    
    class Tree::node{
        friend Tree; //Tree needs access to node for its root
        friend iterator; //iterator needs access to node for its current node
    private:
        /**
         Constructor creates a new node with the provided value with left, right, and parent set to nullptr.
         
         @param _val the value that node will wrap around
         */
        node(double _val);
        node *left, *right, *parent; //pointers to the nodes surrounding the current node
        double val; //the value node wraps around
        
        /**
         Recursive function passes a new node between existing nodes until it has reached its proper location.
         
         @param n the node to be inserted
         @return true if the node is inserted (is unique), false if the node is not inserted (is a duplicate of an existing node)
         */
        bool insertNode(node* n);
    };
    
    class Tree::iterator{
        friend Tree; //to allow iterator modifications by Tree operations
    private:
        /**
         Constructor creates a new iterator with a given current node and Tree to manage.
         
         @param n the current node
         @param container the Tree iterator will manage
         */
        iterator(node* n, const Tree* container);
        node *curr; //the node at the current location
        const Tree *container; //the Tree iterator manages
    public:
        /**
         Preincrement operator moves iterator to the node in Tree with the next highest value.
         
         @return the original iterator with the new current node.
         */
        iterator &operator++();
        
        /**
         Postincrement operator moves iteraotr to the node in Tree with the next highest value but provides the original iterator before it was moved.
         
         @return an iterator at the original node by copy
         */
        iterator operator++(int);
        
        /**
         Dereference operator provides the value of the iterator's current node (which can be modified).
         
         @return the current node's value
         */
        double& operator*() const;
        
        /**
         Arrow operator provides a pointer to the location in memory of the current node's value.
         
         @return a pointer to the current node's value
         */
        double* operator->() const;
        
        /**
         Operator tells if this iterator and another share the same current node and Tree.
         
         @param rhs the iterator to be compared with this iterator
         @return true if the current nodes and Trees are the same, false otherwise
         */
        bool operator==(const iterator& rhs) const; // comparisons
    };
    
    /**
     Operator tells if two iterators share the same current node and Tree (using operator==).
     
     @param lhs the first iterator to be compared
     @param rhs the second iterator to be compared
     @return true if their current nodes and Trees are the same, false otherwise
     */
    bool operator!=(const Tree::iterator& lhs, const Tree::iterator& rhs);
} //ending namespace

#endif

