#ifndef __VERTEX__
#define __VERTEX__

#include <vector>
#include <list>
#include <unordered_map>

class Edge;
class Goldberg_flow;

class Vertex
{
    friend class Goldberg_flow;
private:
    int m_height;
    int m_excess_flow;
    std::vector<Edge*> m_edges;
    // False if the vertex is not inserted to any list
    bool m_excessflow_inserted;
    std::list<Vertex*>::iterator m_excessflow_iterator;
    std::list<Edge*> m_unsaturated;
public:
    Vertex() : 
       m_height(0), m_excess_flow(0), m_excessflow_inserted(false) {}
    Vertex(int height) : 
        m_height(height), m_excess_flow(0), m_excessflow_inserted(false) {}

    int get_height() const {return m_height;}
    int get_excess_flow() const {return m_excess_flow;}
};

#endif // __VERTEX__