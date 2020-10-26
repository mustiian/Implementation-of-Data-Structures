#ifndef __NODE_H__
#define __NODE_H__

enum Color { BLACK, RED };

class RedBlackTree;

class Node
{
    friend class RedBlackTree;
public: 
    int key;
    Node();
    Node(int key, Node* parent, Node* left, Node* right);
    ~Node();

    Node* GetParent() {return parent;}
    Node* GetLeftChild() {return left;}
    Node* GetRightChild() {return right;}
    Color GetColor() {return color;}
private:
    int leftDepth;
    Node* parent;
    Node* left;
    Node* right;
    Color color;
};

Node::Node(int key, Node* parent=nullptr, Node* left=nullptr, Node* right=nullptr) 
{
    this->key = key;
    this->parent = parent;
    this->left = left;
    this->right = right;
    if (left) left->parent = this;
    if (right) right->parent = this;
    leftDepth = 0;
}

Node::~Node()
{
}
#endif // __NODE_H__