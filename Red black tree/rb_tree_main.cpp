#include "rb_tree_test.h"

int main(int argc, char const *argv[])
{
    RedBlackTreeTester tester;
    RedBlackTree t;

    tester.TestRandomSequence(100, 14);
    tester.TestSequence(100);
    tester.TestRandomPermutation(155, 87);

    return 0;
}