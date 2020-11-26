#include "golberg_flow_test.h"

int main(int argc, char const *argv[])
{
    Golberg_flow g (8, 5, 1, 5);
    g.add_edge(1, 2, 30);
    return 0;
}
