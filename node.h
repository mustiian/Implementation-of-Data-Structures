#ifndef __NODE_H__
#define __NODE_H__

enum Color { NONE, BLACK, RED };

class Node
{
public:
    Node* parent;
    Node* left;
    Node* right;
    Color color;
    int key;

     Node(int key, Node* parent);
    ~Node();
};

Node::Node(int key, Node* parent)
{
     this->key = key;
    this->parent = parent;
    this->left = nullptr;
    this->right = nullptr;
    this->color = NONE;
}

Node::~Node()
{
}
#endif // __NODE_H__