#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include "node.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <ctime>
#include <stdlib.h>

class RedBlackTree
{
public: 
    RedBlackTree();
    ~RedBlackTree();

    void Insert(int key);

    void Delete(int key);

    bool Find(int key);
    
    int KMin(int k);

    void Print();

    Node* Head() {return head;}

private:
    void Rotate(Node* node);

    void PrintNode(Node* node);

    Node* FindNode(int key);

    void FixUp(Node* node);

    Node* head;
};


RedBlackTree::RedBlackTree()
{
    head = nullptr;
}

RedBlackTree::~RedBlackTree()
{
    Node* node = head;

    while (node) {
        Node* next;
        if (node->right) {
            next = node->right;
            node->right = nullptr;
        } else if (node->left) {
            next = node->left;
            node->left = nullptr;
        } else {
            next = node->parent;
            delete node;
        }
        node = next;
    }
}

/**
 * Create new node with the key and insert it to the tree 
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} key    : Desired key number  
 */
void RedBlackTree::Insert(int key)
{
    if (!head){
        head = new Node(key, BLACK);
        return;
    }

    if (FindNode(key))
        return;

    Node* node = head;
    while (node->key != key)
    {
        if (key < node->key) {
            if (!node->left)
                node->left = new Node(key, RED, node);

            node->quantityLeftNodes++;
            node = node->left;
        } else {
            if (!node->right)
                node->right = new Node(key, RED, node);
            node = node->right;
        }
    }

   FixUp(node);
}

/**
 * Delete the key with the same key.
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} key    : Desired key number 
 */
void RedBlackTree::Delete(int key) 
{
    
}

/**
 * Find the key with the same key.
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} key    : Desired key number 
 * @return {bool}       : Return false if not found
 */
bool RedBlackTree::Find(int key) 
{
    return FindNode(key) == nullptr? false : true;
}


/**
 * Rotate the node right or left, depends on the parent.
 * 
 * @param  {Node*} node : Given node for rotation
 */
void RedBlackTree::Rotate(Node* node) 
{
    if (node->parent){
        if (node->parent->right == node){ // left rotation
            if (node->left)
                node->left->parent = node->parent;
            node->quantityLeftNodes += node->parent->quantityLeftNodes + 1; 
            
            node->parent->right = node->left;
            node->left = node->parent;
        } else {                        // right rotation
            if (node->right)
                node->right->parent = node->parent;
            node->parent->quantityLeftNodes -= node->quantityLeftNodes + 1; 

            node->parent->left = node->right;
            node->right = node->parent;
        }

        if (node->parent->parent)
            if (node->parent->parent->right == node->parent)
                node->parent->parent->right = node;
            else
                node->parent->parent->left = node;
        else
            head = node;
        
        Node* originalParent = node->parent;
        node->parent = node->parent->parent;
        originalParent->parent = node;
    }
}

/**
 * Print info about the node
 * 
 * @param  {Node*} node : Target node
 */
void RedBlackTree::PrintNode(Node* node) 
{
    if (node == nullptr || (!node->left && !node->right))
        return; 

    std::string Color;

    if (node->left){
        Color = node->left->color == BLACK? 'B': 'R'; 
        std::cout << Color + std::to_string(node->left->key) + " <- ";
    }
    else
        std::cout << "      ";

    Color = node->color == BLACK? 'B': 'R'; 
        std::cout << Color + std::to_string(node->key);

    if (node->right){
        Color = node->right->color == BLACK? 'B': 'R'; 
        std::cout << " -> " + Color + std::to_string(node->right->key);
    }

    std::cout << std::endl;
    
    PrintNode(node->left);
    PrintNode(node->right);
}

Node* RedBlackTree::FindNode(int key) 
{
    Node * node = head;
    while (node && (node->key != key))
    {
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node;
}

/**
 * Fix up the tree after insertion (down up)
 * 
 * @param  {Node*} node : Node to fix up
 */
void RedBlackTree::FixUp(Node* node) 
{
    if (!node)
        return;

    while (node->parent && node->parent->color == RED)
    {   // Red uncle case
        if (node->Uncle() && node->Uncle()->color == RED){
            node->parent->color = BLACK;
            node->Uncle()->color = BLACK;
            node->parent->parent->color = RED;
            node = node->parent->parent;
        }
        else // Black uncle or no uncle
        {
            // Red nodes in triangle case
            if ((node->parent == node->parent->parent->left && node == node->parent->right) || 
                (node->parent == node->parent->parent->right && node == node->parent->left)){
                Node * originalParent = node->parent;
                Rotate(node);
                node = originalParent;
            }
            node->parent->color = BLACK; 
            node->parent->parent->color = RED;
            Rotate(node->parent);
        }
    }
    head->color = BLACK;
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
    Node* node = head;
    int position = k;

    while (position > 0) // simplify to 1 while
    {
       if (node->left && node->quantityLeftNodes >= position){
            node = node->left;
        }
        else if (position == node->quantityLeftNodes + 1)
            return node->key;
        else
        {
            if (!node->right)
                return INT32_MAX;

            position -= node->quantityLeftNodes + 1;
            node = node->right;
        }
    }
    return node->key;
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