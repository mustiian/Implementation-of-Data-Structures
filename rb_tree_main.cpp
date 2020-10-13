#include "rb_tree_test.h"

int main(int argc, char const *argv[])
{
    int i =1;
    i++;

    Node * node = new Node(i, nullptr);
    free(node);
    
    return 0;
}