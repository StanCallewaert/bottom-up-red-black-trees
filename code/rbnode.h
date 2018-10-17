#ifndef RBNODE_H
#define RBNODE_H

#include "rbtree.h"

enum Color {red,black};

template <class Key>
class RBTree;

template <class Key>
class RBNode {
    friend class RBTree<Key>;
    public:
        RBNode():parent(0){}
        RBNode(const Key& key):key{key},parent(0),color(red){};
        RBNode(Key&& key):key{move(key)},parent(0),color(red){};
        
        RBTree<Key>& returnChild(const bool left);
        bool isLeftChild(RBNode<Key>* node);
        RBTree<Key>* returnParent(RBTree<Key>* root);
        
        Key key;
        RBNode<Key>* parent;
        RBTree<Key> left, right;
        Color color;
};

template <class Key>
RBTree<Key>& RBNode<Key>::returnChild(const bool left){
    return left ? this->left : this->right;
}

template <class Key>
bool RBNode<Key>::isLeftChild(RBNode<Key>* node) {
    return &(*(this->left)) == node;
}

template <class Key>
RBTree<Key>* RBNode<Key>::returnParent(RBTree<Key>* root) {
    RBNode<Key>* parentNode = this->parent;
    
    if (parentNode) {
        RBNode<Key>* grandparentNode = parentNode->parent;
        
        if (grandparentNode) {
            return &(grandparentNode->returnChild(grandparentNode->isLeftChild(parentNode)));
        }
        
        return root;
    }
    
    return nullptr;
}

#endif

