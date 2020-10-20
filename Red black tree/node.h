#ifndef __NODE_H__
#define __NODE_H__

enum Color { BLACK, RED };

class Node
{
public: // should be private
    int key;

    Node(int key, Node* parent);
    ~Node();

    Node* GetParent() {return parent;}
    Node* GetLeftChild() {return left;}
    Node* GetRightChild() {return right;}
    Color GetColor() {return color;}
private:
    Node* parent;
    Node* left;
    Node* right;
    Color color;
};

Node::Node(int key, Node* parent)
{
    this->key = key;
    this->parent = parent;
    this->left = nullptr;
    this->right = nullptr;
}

Node::~Node()
{
}
#endif // __NODE_H__