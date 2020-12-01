#ifndef __EDGE__
#define __EDGE__

#include "vertex.h"

class Edge
{
    friend class Goldberg_flow;
private:
    Vertex *m_start, *m_end;
    int m_flow;
    int m_capacity;
public:
    Edge() : m_start(nullptr), m_end(nullptr), m_flow(0), m_capacity(0) {}
    Edge(Vertex *start, Vertex *end, int capacity) : 
        m_start(start), m_end(end), m_capacity(capacity) {}

   Vertex* get_start() const {return m_start;}
   Vertex* get_end() const {return m_end;}
   bool is_outgoing(const Vertex* v) { return m_start == v; }
   int get_flow() const {return m_flow;}
   int get_capacity() const {return m_capacity;}
};

#endif // __EDGE__