#include "rb_tree_test.h"

int main(int argc, char const *argv[])
{
    RedBlackTree t;
    string operation;
    int value;

    while (cin >> operation >> value)
    {
        if (operation == "I")
            t.Insert(value);
        else if (operation == "F")
            cout << t.KMin(value) << endl;
        else if (operation == "D")
            t.Delete(value);
        else
        {
            cout << "Invalid input" << endl;
            return 1;
        }
    }
    return 0;
}