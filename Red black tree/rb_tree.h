#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include "node.h"
#include <iostream>
#include <vector>
#include <string>

class RedBlackTree
{
public: 
    RedBlackTree();
    ~RedBlackTree();

    Node* Insert(int key);

    Node* Delete(int key);

    Node* Find(int key);
    
    int KMin(int k);

    void Print();

private:
    void RotateLeft(Node* head);

    void RotateRight(Node* head);

    void PrintNode(Node* head, int space);

    Node* head;
    int printSpace = 10;
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
 * Print info about the node
 * 
 * @param  {Node*} node : Target node
 * @param  {int} space  : Space between nodes
 */
void RedBlackTree::PrintNode(Node* node, int space) 
{
    if (node == nullptr)
        return; 

    space += this->printSpace;
    PrintNode(node->GetRightChild(), space);
    for (int i = this->printSpace; i < space; i++)
        std::cout << "\t";
    std::cout << node->key << std::endl;
    PrintNode(node->GetLeftChild(), space);
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
/**
 * Print all nodes of the tree
 * 
 */
void RedBlackTree::Print() 
{
    PrintNode(this->head, 0);
}

#endif // __RB_TREE_H__