#ifndef __EDGE
#define __EDGE__

#include "vertex.h"

class Edge
{
    friend class Golberg_flow;
private:
    Vertex &m_start, &m_end;
    int m_flow;
    int m_reserve;
    int m_capacity;
public:
    Edge(Vertex &start, Vertex &end, int capacity) : 
        m_start(start), m_end(end), m_capacity(capacity) {}

   Vertex& get_start() const {return m_start;}
   Vertex& get_end() const {return m_end;}
   int get_flow() const {return m_flow;}
   int get_reserve() const {return m_reserve;}
   int get_capacity() const {return m_capacity;}
};

#endif // __EDGE__