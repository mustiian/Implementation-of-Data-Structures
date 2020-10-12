#include "rb_tree.h"
#include<iostream>
#include <string>

using namespace std;

#define TEST(condition, message) do { if (!(condition)) printError(message); } while (0)

void printError(const string& error){
    cerr << "Test error: " << error << endl;
}

class RedBlackTreeTester
{
private:
    /* data */
public:
    RedBlackTreeTester(/* args */);
    ~RedBlackTreeTester();
};

RedBlackTreeTester::RedBlackTreeTester(/* args */)
{
}

RedBlackTreeTester::~RedBlackTreeTester()
{
}