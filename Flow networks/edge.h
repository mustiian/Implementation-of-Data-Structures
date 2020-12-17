#ifndef __EDGE__
#define __EDGE__

#include "vertex.h"

class Edge
{
    friend class Goldberg_flow;
private:
    Vertex *m_start, *m_end;
    int m_flow;
    int m_reverse_flow;
    int m_capacity;
    bool m_unsaturated_inserted;

public:
    Edge() : m_start(nullptr), m_end(nullptr), m_flow(0), 
            m_reverse_flow(0), m_capacity(0), m_unsaturated_inserted(false) {}
    Edge(Vertex *start, Vertex *end, int capacity) : 
        m_start(start), m_end(end), m_flow(0), 
        m_reverse_flow(0), m_capacity(capacity), m_unsaturated_inserted(false) {}

   Vertex* get_start() const {return m_start;}
   Vertex* get_end() const {return m_end;}
   bool is_outgoing(const Vertex* v) const { return m_start == v; }
   int get_flow(const Vertex* v) const {return is_outgoing(v)? m_flow : m_reverse_flow; }
   int get_residual(const Vertex* v) const {return is_outgoing(v)? m_capacity - m_flow : m_flow; }
   Vertex* get_another_vertex(const Vertex* v) const {return v == m_start? m_end : m_start; }
   int get_capacity() const {return m_capacity;}
};

#endif // __EDGE__