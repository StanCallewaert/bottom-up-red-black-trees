#ifndef RBTREE_H
#define RBTREE_H

#include "rbnode.h"

#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <cassert>

using std::unique_ptr;
using std::make_unique;
using std::string;
using std::move;
using std::ostream;
using std::ofstream;
using std::ostringstream;
using std::cout;
using std::endl;

template <class Key>
class RBNode;

template <class Key>
class RBTree : public unique_ptr<RBNode<Key>> {
    public:
        // Use unique pointer methods (default constructor of unique_ptr is used for this class)
        using unique_ptr<RBNode<Key>>::unique_ptr;
        
        // Use the move operator of unique_ptr<RBNode<Key>> as the move operator from RBTree
        RBTree(unique_ptr<RBNode<Key>>&& boom) : unique_ptr<RBNode<Key>> (move(boom)) { }
        
        void rotate(bool left);
        void addBottomUp(const Key& key);
        
        // Use this function to visualize the current graph
        // Just copy the textual output that is in the given file after executing the program
        // and paste it in the textarea of the website: http://webgraphviz.com
        void visualize(const char* filename) const;
    protected:
        // Recursive method that makes sure that the tree stays a RBTree
        // Solved in a bottom-up approach
        void stayRBTreeBottomUp(RBTree<Key>* newNodePtr, RBNode<Key>* parent);
        
        // Returns the pointer to the node (and his parent) that was searched for
        void search(const Key& key, RBTree<Key>*& newNodePtr, RBNode<Key>*& parent);
        
        // Recursively print out the text of each node to be able to visualize the tree
        string visualizeNodesRecusively(ostream& out, int& nullCounter) const;
};

template <class Key>
void RBTree<Key>::rotate(bool left) {
    // Get child of root
    RBTree<Key> child = move((*this)->returnChild(!left));
    
    // Move beta (image in readme.md)
    (*this)->returnChild(!left) = move(child->returnChild(left));
    
    // Move root (image in readme.md)
    child->returnChild(left) = move(*this);
    
    // Move child (image in readme.md)
    *this = move(child);
    
    // Restore parent pointers
    (*this)->parent = (*this)->returnChild(left)->parent;
    (*this)->returnChild(left)->parent = this->get();
    
    // If alpha is not null, restore its parent pointer as well
    if ((*this)->returnChild(left)->returnChild(!left)) {
        (*this)->returnChild(left)->returnChild(!left)->parent = (*this)->returnChild(left).get();
    }
}

template <class Key>
void RBTree<Key>::addBottomUp(const Key& key) {
    // Initialize newNodePtr and parent to get their real values in the search function
    RBTree<Key>* newNodePtr;
    RBNode<Key>* parent;
    
    // Find the spot (and his parent) where the new node has to be added to
    this->search(key, newNodePtr, parent);
    
    // Only add the new key if it does not exist in the red-black tree yet
    if (!*newNodePtr) {
        // Create new node and add parent pointer
        RBTree<Key> tree = make_unique<RBNode<Key>>(key);
        *newNodePtr = move(tree);
        (*newNodePtr)->parent = parent;
        
        // Make sure that there is no red node with a red parent
        // and make sure that the black depth for each virtual node is equal
        this->stayRBTreeBottomUp(newNodePtr, parent);
        
        // Make root black
        (*this)->color = black;
    }
}

template <class Key>
void RBTree<Key>::stayRBTreeBottomUp(RBTree<Key>* newNodePtr, RBNode<Key>* parent) {
    // Solve conflict if the added node has a red parent
    if (parent && parent->color == red) {
        RBTree<Key>* grandparent = parent->parent && parent->parent->parent ? &(parent->parent->parent->returnChild(parent->parent->parent->isLeftChild(parent->parent))) : this;
        bool isParentLeftChildOfGrandparent = (*grandparent)->isLeftChild(parent);
        RBTree<Key>* uncle = &((*grandparent)->returnChild(!isParentLeftChildOfGrandparent));

        if (*uncle && (*uncle)->color == red) {
            (*uncle)->color = black;
            (*grandparent)->color = red;
            parent->color = black;
            
            // Grandparent is red, solve problems if grandgrandparent is also red
            this->stayRBTreeBottomUp(grandparent, (*grandparent)->parent);
        } else {
            if (parent->isLeftChild(&(**newNodePtr)) != isParentLeftChildOfGrandparent) {
                (*grandparent)->returnChild(isParentLeftChildOfGrandparent).rotate(isParentLeftChildOfGrandparent);
            }

            grandparent->rotate(!isParentLeftChildOfGrandparent);

            // Where uncle used to be now needs to become red
            (*grandparent)->returnChild(!isParentLeftChildOfGrandparent)->color = red;
            (*grandparent)->color = black;
        }
    }
}

template <class Key>
void RBTree<Key>::search(const Key& key, RBTree<Key>*& newNodePtr, RBNode<Key>*& parent){
    newNodePtr = this;
    parent = nullptr;
    
    while (*newNodePtr && (*newNodePtr)->key !=key){
        parent = newNodePtr->get();
        newNodePtr = &((*newNodePtr)->returnChild(((*newNodePtr)->key > key)));
    };
};


template <class Key>
void RBTree<Key>::visualize(const char* filename) const {
    ofstream out(filename);
    assert(out);
    
    // Nullptr nodes need to get their own number, hence the nullcounter
    int nullCounter = 0;
    out<<"digraph {\n";
    
    // Recursively print out the text of each node to be able to visualize the tree
    this->visualizeNodesRecusively(out, nullCounter);
    
    out<<"}";
}

template <class Key>
string RBTree<Key>::visualizeNodesRecusively(ostream& out, int& nullCounter) const {
    ostringstream RBTreeString;
    
    if (!*this){
        RBTreeString << "null" << ++nullCounter;
        out << RBTreeString.str() << " [shape=point];\n";
    }
    else{
        RBTreeString << '"' << (*this)->key<<'"';
        out << RBTreeString.str() << "[label=\"" << (*this)->key << "\"]";
        if ((*this)->color == red)
            out<<"[color=red]";
        out<<";\n";
        string leftChild = (*this)->left.visualizeNodesRecusively(out, nullCounter);
        string rightChild = (*this)->right.visualizeNodesRecusively(out, nullCounter);
        out << RBTreeString.str() << " -> " << leftChild << ";\n";
        out << RBTreeString.str() << " -> " << rightChild << ";\n";
    };
    
    return RBTreeString.str();
}

#endif