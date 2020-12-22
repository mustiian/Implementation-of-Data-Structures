#include "goldberg_flow.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    int vertices, edges, start, end, cap;

    std::cin >> vertices >> edges >> start >> end;

    Goldberg_flow g(vertices, start, end);

    for (int i = 0; i < edges; i++)
    {
        std::cin >> start >> end >> cap;
        g.add_edge(start, end, cap);
    }

    std::cout << g.get_max_flow() << std::endl;
    g.print_flow_edges();

    return 0;
}
