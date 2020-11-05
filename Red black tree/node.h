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
    Node* Sibling();
private:
    int quantityLeftNodes;
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
    quantityLeftNodes = 0;
}

Node::~Node()
{
}

Node* Node::Uncle() 
{
    if (!this->parent)
        return nullptr;

    return this->parent->Sibling();
}

Node* Node::Sibling() 
{
    if (!this->parent)
        return nullptr;
    
    if (this->parent->left == this)
        return this->parent->right;
    else 
        return this->parent->left;
}
#endif // __NODE_H__