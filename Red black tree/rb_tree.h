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

    void FixDelete(Node* node);

    Node* Min(Node* node);

    void Replace(Node* node, Node* dest);

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
 * Create new node with the key and insert it to the tree.
 * if there is already a node with the same key, then ignores the key.  
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
    Node* node = FindNode(key);

    if (node == nullptr)
        return;

    if (node->left && node->right){
        Node* swap = Min(node->right);
        node->key = swap->key;
        node = swap;
    }

    Node* replaceNode;

    if (node->left){
        replaceNode = node->left;
        Replace(node, replaceNode);
    } else if (node->right){
        replaceNode = node -> right;
        Replace(node, replaceNode);
    } else{
        replaceNode = node;
    }
        
    if (node->color == BLACK) {
		if (replaceNode->color == RED)
			replaceNode->color = BLACK;
		else
			FixDelete(replaceNode);
	}

    //FixLeftNodesQuantity(replaceNode); TODO
    
    if (replaceNode == node && node->parent){
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else 
            node->parent->right = nullptr;
    }

    if (node == head && !node->left && !node->right)
        head = nullptr;

	delete node;
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
    if (node == head)
        std::cout << "==============" << std::endl;

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

void RedBlackTree::FixDelete(Node* node) 
{
    Node* sibling = nullptr;
    if (node->parent && node->color == BLACK)
    {
        sibling = node->Sibling();
        // Case 2
        if (sibling && sibling->color == RED){
            Rotate(sibling);
            sibling->color = BLACK;
            node->parent->color = RED;
            sibling = node->Sibling();
        }
        ColorType rightSibColor = (!sibling->right or sibling->right->color == BLACK)? BLACK : RED;
        ColorType leftSibColor = (!sibling->left or sibling->left->color == BLACK)? BLACK : RED;

        if (sibling->color == BLACK){
            // Case 3
            if (node->parent->color == BLACK && 
                    rightSibColor == BLACK && leftSibColor == BLACK){
                sibling->color = RED;
                FixDelete (node ->parent);
            } 
            // Case 4
            else if (node->parent->color == RED && 
                rightSibColor == BLACK && 
                leftSibColor == BLACK){
                node->parent->color = BLACK;
                sibling->color = RED;
            // Case 5 (as left node)
            } else if (node == node->parent->left && rightSibColor == BLACK &&
                    leftSibColor == RED){
                sibling->color = RED;
                sibling->left->color = BLACK;
                Rotate(sibling->left);
            // Case 5 (as right node)
            } else if (node == node->parent->right && leftSibColor == BLACK &&
                    rightSibColor == RED){
                sibling->color = RED;
                sibling->right->color = BLACK;
                Rotate(sibling->right);
                }
            }
            sibling = node->Sibling();
            rightSibColor = (!sibling->right or sibling->right->color == BLACK)? BLACK : RED;
            leftSibColor = (!sibling->left or sibling->left->color == BLACK)? BLACK : RED;
            // Case 6 (as right node)
            if (sibling->left && node == node->parent->right && 
                    leftSibColor == RED){
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                Rotate(sibling);
            // Case 6 (as left node)
            } else if (sibling->right && node == node->parent->left && 
                    rightSibColor == RED){
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                Rotate(sibling);
            }
        }
}

Node* RedBlackTree::Min(Node* node) 
{
    Node * targetNode = node;

    while (targetNode->left != nullptr)
    {
        targetNode = targetNode->left;
    }

    return targetNode;
}

/**
 * Replace node with the destination node
 * 
 * @param  {Node*} node : Original node
 * @param  {Node*} dest : Destination node
 */
void RedBlackTree::Replace(Node* node, Node* dest) 
{
    if (!node->parent)
        head = dest;
    else if (node == node->parent->left)
        node->parent->left = dest;
    else
        node->parent->right = dest;

    if (dest)
        dest->parent = node->parent;
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