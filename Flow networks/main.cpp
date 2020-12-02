#include "goldberg_flow.h"

int main()
{
    Goldberg_flow g (4, 1, 4);
    g.add_edge(3, 1, 17);
    g.add_edge(1, 2, 10);
    g.add_edge(1, 3, 5);
    g.add_edge(3, 2, 3);
    g.add_edge(2, 3, 1);
    g.add_edge(2, 4, 2);
    g.add_edge(3, 4, 7);

    g.get_max_flow();

    return 0;
}
