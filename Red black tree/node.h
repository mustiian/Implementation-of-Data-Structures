#ifndef __NODE_H__
#define __NODE_H__

enum ColorType { BLACK, RED };

class RedBlackTree;

class Node
{
    friend class RedBlackTree;
public: 
    int key;
    Node();
    Node(int key, ColorType color, Node* parent, Node* left, Node* right);
    ~Node();

    Node* Parent() {return parent;}
    Node* LeftChild() {return left;}
    Node* RightChild() {return right;}
    ColorType Color() {return color;}
    Node* Uncle();
private:
    int leftDepth;
    Node* parent;
    Node* left;
    Node* right;
    ColorType color;
};

Node::Node(int key, ColorType color, Node* parent=nullptr, Node* left=nullptr, Node* right=nullptr)
{
    this->key = key;
    this->parent = parent;
    this->left = left;
    this->right = right;
    this->color = color;
    if (left) left->parent = this;
    if (right) right->parent = this;
    leftDepth = 0;
}

Node::~Node()
{
}

Node* Node::Uncle() 
{
    Node* grandparent = nullptr;

    if (this->parent)
        grandparent = this->parent->parent;

    if (!grandparent)
        return nullptr;

    if (this->parent == grandparent->left)
        return grandparent->right;
    else
        return grandparent->left;
}
#endif // __NODE_H__