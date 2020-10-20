#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include "node.h"

class RedBlackTree
{
public: 
    RedBlackTree();
    ~RedBlackTree();

    Node* Insert(int key);

    Node* Delete(int key);

    Node* Find(int key);
    
    int KMin(int k);

private:
    void RotateLeft(Node* head);

    void RotateRight(Node* head);

    Node* head;
};


RedBlackTree::RedBlackTree()
{
}

RedBlackTree::~RedBlackTree()
{
}

/**
 * Create new node with the key and insert it to the tree 
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} key    : Desired key number  
 * @return {Node*}      : New node head of the tree
 */
Node* RedBlackTree::Insert(int key)
{
    return nullptr;
}

/**
 * Delete the key with the same key.
 * Return nullptr if there is no node with the same key.
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} key    : Desired key number 
 * @return {Node*}      : New node head of the tree
 */
Node* RedBlackTree::Delete(int key) 
{
    return nullptr;
    
}
/**
 * Find the key with the same key.
 * Return nullptr if there is no node with the same key.
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} key    : Desired key number 
 * @return {Node*}      : The node with the same key
 */
Node* RedBlackTree::Find(int key) 
{
    return nullptr;
}

/**
 * Rotate node to the left 
 * 
 * @param  {Node*} head : Rotated head node
 */
void RedBlackTree::RotateLeft(Node* head) 
{
    
}

/**
 * Rotae node to the right 
 * 
 * @param  {Node*} head : Rotated head node
 */
void RedBlackTree::RotateRight(Node* head) 
{
    
}

/**
 * Return the Kth minimum number
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} k      : Index number
 * @return {int}        : The Kth minimum number
 */
int RedBlackTree::KMin(int k) 
{
    
}

#endif // __RB_TREE_H__