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
    TestRedNodes(Node* head);
    TestHeadNode(Node* head);
    TestLeavesNodes(Node* head);
    TestPathFromHeadToLeaves(Node* head);

    TestIntegrity(Node* node);

    RedBlackTreeTester();
    ~RedBlackTreeTester();
};

RedBlackTreeTester::RedBlackTreeTester()
{
}

RedBlackTreeTester::~RedBlackTreeTester()
{
}


#endif // __RB_TREE_TEST_H__