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

    bool Find(int key);
    
    int KMin(int k);

    void Print();

private:
    void RotateLeft(Node* head);

    void RotateRight(Node* head);

    void PrintNode(Node* node);

    Node* FindNode(int key);

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
bool RedBlackTree::Find(int key) 
{
    return false;
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
 */
void RedBlackTree::PrintNode(Node* node) 
{
    if (node == nullptr)
        return; 

    char Color;
    Node* left = node->GetLeftChild(); 
    Node* right = node->GetRightChild();

    if (!left && !right)
        return;

    if (left){
        Color = left->GetColor() == BLACK? 'B': 'R'; 
        std::cout << Color + std::to_string(node->key) + " <- ";
    }

    Color = node->GetColor() == BLACK? 'B': 'R'; 
        std::cout << Color + std::to_string(node->key);

    if (right){
        Color = right->GetColor() == BLACK? 'B': 'R'; 
        std::cout << " -> " + Color + std::to_string(node->key);
    }

    std::cout << std::endl;
    
    PrintNode(left);
    PrintNode(right);
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
    PrintNode(this->head);
}

#endif // __RB_TREE_H__