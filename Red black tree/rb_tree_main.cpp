#include "rb_tree_test.h"

int main(int argc, char const *argv[])
{
    RedBlackTree t;
    RedBlackTreeTester tester;

    t.Insert(10);
    t.Insert(13);
    t.Insert(7);
    t.Insert(20);
    t.Insert(23);
    t.Insert(26);
    t.Insert(5);
    t.Insert(8);
    t.Insert(3);
    t.Insert(38);
    t.Insert(11);
    t.Insert(16);
    t.Insert(15);

    t.Print();

    tester.TestIntegrity(t.Head(), 3, 38);
    tester.TestNumberOfBlackNodes(t.Head());

    return 0;
}