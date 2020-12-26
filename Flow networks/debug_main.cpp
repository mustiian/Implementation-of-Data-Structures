#include "goldberg_flow_test.h"
#include <deque>

int main()
{
    Golberg_flow_tester t(40);

    t.random_graph_1();

    t.simple_graph_1();
    t.simple_graph_2();
    t.simple_graph_3();
    //t.random_graph(400, 10);
    t.test_random();

    return 0;
}
