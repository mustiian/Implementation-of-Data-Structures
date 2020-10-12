#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include "node.h"

class RedBlackTree
{
public:
    Node* Insert(Node* head, int key);

    Node* Delete(Node* head, int key);

    Node* Find(Node* head, int key);
    
    Node* GetParent(Node* head, int key);

    RedBlackTree();
    ~RedBlackTree();
};

#endif // __RB_TREE_H__