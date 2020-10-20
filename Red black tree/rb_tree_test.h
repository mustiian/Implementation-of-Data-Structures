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
            << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
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
 * Test red node. Its GetParent() is not red and the children are black.
 * 
 * @param  {Node*} node : Tested node
 */
void RedBlackTreeTester::TestColor(Node* node) 
{
    string err_message = to_string(node->key) + " node: red test failed";

    // Test that root is always black
    TEST(!node->GetParent() && node->GetColor() == BLACK, err_message);
    // Test that red node has only black children
    TEST(node->GetColor() == RED && (!node->GetLeftChild() || node->GetLeftChild()->GetColor() == BLACK), err_message); 
    TEST(node->GetColor() == RED && (!node->GetRightChild() || node->GetRightChild()->GetColor() == BLACK), err_message);
    // Test that red node hasn't red GetParent() 
    TEST(node->GetColor() == RED && (!node->GetParent() || node->GetParent()->GetColor() != RED), err_message);
}

/**
 * Test number of black nodes during the path from the head node to leaves nodes.
 * All paths should have the same number of black nodes.
 * 
 * @param  {Node*} head : Head of the tree
 * @param  {int} depth  : Number of GetParent()'s black nodes 
 * @return {int}        : New number of the black nodes during the path
 */
int RedBlackTreeTester::TestPathFromHeadToLeaf(Node* head, int depth) 
{
    int leftDepth = 0, rightDepth = 0;

    // If the head is leaf then has same depth as GetParent()
    if (head == nullptr)
        return depth;

    // Increase number of black nodes if current node is black
    if (!head->GetColor() == BLACK)
        depth += 1;
    
    if (head->GetLeftChild()) 
        leftDepth = TestPathFromHeadToLeaf(head->GetLeftChild(), depth);
    else // If head has no GetLeftChild() child then GetLeftChild() depth is the same
        leftDepth = depth;

    if (head->GetRightChild())
        rightDepth = TestPathFromHeadToLeaf(head->GetRightChild(), depth);
    else // If head has no GetRightChild() child then GetRightChild() depth is the same
        rightDepth = depth;
            
    string err_message = to_string(head->key) + "node: depth test failed, GetLeftChild() " + 
                            to_string(leftDepth) + ", GetRightChild() " + to_string(rightDepth);

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
        head = tree.Insert(i);

    for (int i = 2; i < length; i+=2)
        TEST(tree.Find(i) != nullptr, to_string(i) + "key: sequence find test failed.");

    for (int i = 1; i < length; i+=2)    
        head = tree.Delete(i);

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
    // Improve test message for each TEST
    string err_message = to_string(node->key) + "node: integrity test failed";

    if(!node)
        return;

    TEST(!node->GetLeftChild() || node->GetLeftChild()->GetParent() == node, err_message);
    TEST(!node->GetRightChild() || node->GetRightChild()->GetParent() == node, err_message);
    TEST( node->key >= min || node->key <= max, err_message);
    TEST(!node->GetRightChild() || node->GetRightChild()->key > node->key, err_message); 
    TEST(!node->GetLeftChild() || node->GetLeftChild()->key < node->key, err_message); 
    

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


#endif // __RB_TREE_TEST_H__