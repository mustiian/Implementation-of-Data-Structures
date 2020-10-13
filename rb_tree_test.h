#ifndef __RB_TREE_TEST_H__
#define __RB_TREE_TEST_H__

#include "rb_tree.h"
#include<iostream>
#include <string>

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
    void TestRedNode(Node* node);
    void TestLeafNode(Node* node);
    void TestPathFromHeadToLeaf(Node* head);

    void TestIntegrity(Node* node);

    RedBlackTreeTester();
    ~RedBlackTreeTester();
};

void RedBlackTreeTester::TestRedNode(Node* node) 
{
    string err_message = to_string(node->key) + " node is not red";
    TEST(node->color == RED, err_message);
}

void RedBlackTreeTester::TestLeafNode(Node* node) 
{
    
}

void RedBlackTreeTester::TestPathFromHeadToLeaf(Node* head) 
{
    
}

void RedBlackTreeTester::TestIntegrity(Node* node) 
{
    
}

RedBlackTreeTester::RedBlackTreeTester()
{
}

RedBlackTreeTester::~RedBlackTreeTester()
{
}


#endif // __RB_TREE_TEST_H__