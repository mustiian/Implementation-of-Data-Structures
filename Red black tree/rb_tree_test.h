#ifndef __RB_TREE_TEST_H__
#define __RB_TREE_TEST_H__

#include "rb_tree.h"
#include<iostream>
#include <string>
#include <cstdlib>

using namespace std;

#define TEST(expression, message) assert(#expression, __FILE__, __LINE__, expression, message);

void assert(const char* expr_str, const char* file, int line, bool expr, const string& message){
    if (!expr)
    {
        cerr << "Assert failed:\t" << message << "\n"
            << "Expected:\t" << expr_str << "\n"
            << "Source:\t" << file << ", line " << line << "\n";
        abort();
    }
}

class RedBlackTreeTester
{
private:
    
public:
    void TestColor(Node* node);
    int TestNumberOfBlackNodes(Node* head);

    void TestSequence(int length);

    void TestIntegrity(Node* node, int min, int max);

    RedBlackTreeTester();
    ~RedBlackTreeTester();
private:
    string KeyToString(Node* node);
};
/**
 * Test red node. Its GetParent() is not red and the children are black.
 * 
 * @param  {Node*} node : Tested node
 */
void RedBlackTreeTester::TestColor(Node* node) 
{
    // Test that root is always black
    TEST(node->GetParent() || node->GetColor() == BLACK, 
        KeyToString(node) + " node: root is red");
    // Test that red node has only black children
    TEST(node->GetColor() == BLACK || !node->GetLeftChild() || node->GetLeftChild()->GetColor() == BLACK, 
        KeyToString(node) + " node: red node has red left child"); 
    TEST(node->GetColor() == BLACK || !node->GetRightChild() || node->GetRightChild()->GetColor() == BLACK, 
        KeyToString(node) + " node: red node has red right child");
    // Test that red node hasn't red parent
    TEST(node->GetColor() == BLACK || !node->GetParent() || node->GetParent()->GetColor() == BLACK, 
        KeyToString(node) + " node: red node has red parent");
}

/**
 * Test number of black nodes during the path from the head node to leaves nodes.
 * All paths should have the same number of black nodes.
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} depth  : Number of GetParent()'s black nodes 
 * @return {int}        : New number of the black nodes during the path
 */
int RedBlackTreeTester::TestNumberOfBlackNodes(Node* node) 
{
    int leftDepth = 0, rightDepth = 0, isBlack = 0;

    // If the head is a leaf
    if (node == nullptr)
        return 1;

    if (!node->GetColor() == BLACK)
        isBlack = 1;
    
    leftDepth = TestNumberOfBlackNodes(node->GetLeftChild());

    rightDepth = TestNumberOfBlackNodes(node->GetRightChild());
            
    string err_message = KeyToString(node) + " node: depth test failed. Left " + 
                        to_string(leftDepth) + ", Right " + to_string(rightDepth);

    TEST (leftDepth == rightDepth, err_message);

    return (leftDepth + isBlack);
}

/**
 * Test Insert, Find, Delete methods for the sequence 
 * 
 * @param  {int} length : Length of the tree
 */
void RedBlackTreeTester::TestSequence(int length) 
{
    RedBlackTree tree;

    for (int i = 2; i < length; i+=2)
        tree.Insert(i);

    for (int i = 2; i < length; i+=2)
        TEST(!tree.Find(i), to_string(i) + " key: could not be found");

    for (int i = 1; i < length; i+=2)    
        tree.Delete(i);
}

/**
 * Test integrity of the given node.
 * 
 * @param  {Node*} node : Tested node 
 * @param  {int} min    : Minimum key
 * @param  {int} max    : Maximum key
 */
void RedBlackTreeTester::TestIntegrity(Node* node, int min, int max) 
{
    if(!node)
        return;

    TEST(!node->GetLeftChild() || node->GetLeftChild()->GetParent() == node, 
        KeyToString(node->GetLeftChild()) + " node: incorrect parent, expected parent " + 
        KeyToString(node) + ", current parent " + KeyToString(node->GetLeftChild()->GetParent()));

    TEST(!node->GetRightChild() || node->GetRightChild()->GetParent() == node, 
        KeyToString(node->GetRightChild()) + " node: incorrect parent, expected parent " + 
        KeyToString(node) + ", current parent " + KeyToString(node->GetRightChild()->GetParent()));

    TEST( node->key >= min || node->key <= max, 
        KeyToString(node->GetRightChild()) + " node: incorrect key. min " + 
        to_string(min) + ", max" + to_string(max));

    TEST(!node->GetRightChild() || node->GetRightChild()->key > node->key, 
        KeyToString(node) + " node: incorrect sequence, right " + 
        KeyToString(node->GetRightChild()) + " is smaller"); 

    TEST(!node->GetLeftChild() || node->GetLeftChild()->key < node->key, 
        KeyToString(node) + " node: incorrect sequence, left " + 
        KeyToString(node->GetLeftChild()) + " is greater"); 

    TestIntegrity(node->GetLeftChild(), min, node->key);
    TestIntegrity(node->GetRightChild(), node->key, max);
    TestColor(node);
}

RedBlackTreeTester::RedBlackTreeTester()
{
}

RedBlackTreeTester::~RedBlackTreeTester()
{
}

string RedBlackTreeTester::KeyToString(Node* node) 
{
    return to_string(node->key);
}


#endif // __RB_TREE_TEST_H__