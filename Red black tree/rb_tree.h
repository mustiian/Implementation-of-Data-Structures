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

    Node* InsertNode(Node* node, int key);

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
    //head = InsertNode(head, key);

    if (!head){
        head = new Node(key, BLACK);
        return;
    }

    Node* node = head;
    while (node->key != key)
    {
        if (key < node->key) {
            if (!node->left)
                node->left = new Node(key, RED, node);
            else
                node->leftDepth++;

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
    return false;
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
            node->leftDepth += node->parent->leftDepth;
            
            node->parent->right = node->left;
            node->left = node->parent;
        } else {                        // right rotation
            if (node->right)
                node->right->parent = node->parent;
            node->parent->leftDepth -= node->leftDepth;

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

void RedBlackTree::FixUp(Node* node) 
{
    while (node->parent && node->parent->color == RED)
    {
        if (node->Uncle() && node->Uncle()->color == RED){
            node->parent->color = BLACK;
            node->Uncle()->color = BLACK;
            node->parent->parent->color = RED;
            node = node->parent->parent;
        }
        else
        {
            node->parent->color = BLACK;
            if (node->parent->parent)
                node->parent->parent->color = RED;
            if (node == node->parent->right || node == node->parent->left){
                node = node->parent;
                Rotate(node);
            }
            else
                Rotate(node->parent->parent);
        }
    }
    head->color = BLACK;
}

Node* RedBlackTree::InsertNode(Node* node, int key) 
{
    if (!node)
        return new Node(key, RED);

    if (node->key == key)
        return nullptr;
    
    if (node->left && node->right)
        if (node->left->color == RED && node->right->color == RED){
            node->left->color = BLACK;
            node->right->color = BLACK;
            node->color = node->color == BLACK? RED : BLACK;
        }
    if (key < node->key)
        node->left = InsertNode(node->left, key);
    else if (key > node->key)
        node->right = InsertNode(node->right, key);

    if (node->left){
        if (node->right)
            if (node->left->color == BLACK && node->right->color == RED)
                Rotate(node->right);
        if (node->left->left)
            if (node->left->color == RED && node->left->left->color == RED)
                Rotate(node->left);
    }

    return node;
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