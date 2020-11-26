#include "golberg_flow.h"

int main(int argc, char const *argv[])
{
    Golberg_flow g (5, 8, 1, 5);
    g.add_edge(1, 2, 30);
    return 0;
}
