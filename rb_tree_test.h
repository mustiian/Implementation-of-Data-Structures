#ifndef __RB_TREE_TEST_H__
#define __RB_TREE_TEST_H__

#include "rb_tree.h"
#include<iostream>
#include <string>
#include <cstdlib>

using namespace std;

#define TEST(condition, message) do { if (!(condition)) printError(message); } while (0)

void printError(const string& error){
    cerr << "Test error: " << error << endl;
    exit(1);
}

class RedBlackTreeTester
{
private:
    
public:
    void TestColor(Node* node);
    int TestPathFromHeadToLeaf(Node* head, int depth);

    void TestSequence(int length);

    void TestIntegrity(Node* node, int min, int max);

    RedBlackTreeTester();
    ~RedBlackTreeTester();
};
/**
 * Test red node. Its parent is not red and the children are black.
 * 
 * @param  {Node*} node : Tested node
 */
void RedBlackTreeTester::TestColor(Node* node) 
{
    string err_message = to_string(node->key) + " node: red test failed";
    // Test that root is always black
    TEST(!node->parent && node->color == BLACK, err_message);
    // Test that red node has only black children
    TEST(node->color == RED && (!node->left || node->left->color == BLACK), err_message);
    TEST(node->color == RED && (!node->right || node->right->color == BLACK), err_message);
    // Test that red node hasn't red parent 
    TEST(node->color == RED && (!node->parent || node->parent->color != RED), err_message);
}

/**
 * Test number of black nodes during the path from the head node to leaves nodes.
 * All paths should have the same number of black nodes.
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} depth  : Number of parent's black nodes 
 * @return {int}        : New number of the black nodes during the path
 */
int RedBlackTreeTester::TestPathFromHeadToLeaf(Node* head, int depth) 
{
    int leftDepth = 0, rightDepth = 0;

    // If the head is leaf then has same depth as parent
    if (head == nullptr)
        return depth;

    // Increase number of black nodes if current node is black
    if (!head->color == BLACK)
        depth += 1;
    
    if (head->left) 
        leftDepth = TestPathFromHeadToLeaf(head->left, depth);
    else // If head has no left child then left depth is the same
        leftDepth = depth;

    if (head->right)
        rightDepth = TestPathFromHeadToLeaf(head->right, depth);
    else // If head has no right child then right depth is the same
        rightDepth = depth;
            
    string err_message = to_string(head->key) + "node: depth test failed, left " + 
                            to_string(leftDepth) + ", right " + to_string(rightDepth);

    TEST (leftDepth == rightDepth, err_message);

    return depth;
}

/**
 * Test Insert, Find, Delete methods for the sequence 
 * 
 * @param  {int} length : Length of the tree
 */
void RedBlackTreeTester::TestSequence(int length) 
{
    Node * head;
    RedBlackTree tree;

    for (int i = 2; i < length; i+=2)
        head = tree.Insert(head, i);

    for (int i = 2; i < length; i+=2)
        TEST(tree.Find(head, i) != nullptr, to_string(i) + "key: sequence find test failed.");

    for (int i = 1; i < length; i+=2)    
        head = tree.Delete(head, i);

    TEST(!head, "Sequence test failed");
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
    string err_message = to_string(node->key) + "node: integrity test failed";

    if(!node)
        return;

    TEST(!node->left || node->left->parent == node, err_message);
    TEST(!node->right || node->right->parent == node, err_message);
    TEST(!node->key >= min || node->key <= max, err_message);
    TEST(!node->right || node->right->key > node->key, err_message);

    TestIntegrity(node->left, min, node->key);
    TestIntegrity(node->right, node->key, max);
    TestColor(node);
}

RedBlackTreeTester::RedBlackTreeTester()
{
}

RedBlackTreeTester::~RedBlackTreeTester()
{
}


#endif // __RB_TREE_TEST_H__