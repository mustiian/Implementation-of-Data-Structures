#include "goldberg_flow.h"

int main()
{
    Golberg_flow_tester t(40);

    t.simple_graph_1();
    t.simple_graph_2();
    t.simple_graph_3();
    t.random_graph(10, 20);
    t.test_random();

    return 0;
}
