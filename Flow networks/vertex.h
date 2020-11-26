#ifndef __VERTEX__
#define __VERTEX__

#include <vector>

class Edge;
class Golberg_flow;

enum Vertex_type {DEFAULT, SOURCE, TARGET};

class Vertex
{
    friend class Golberg_flow;
private:
    int m_ID;
    int m_height;
    int m_excess_flow;
    Vertex_type m_type;
    std::vector<Edge*> m_edges_from;
    std::vector<Edge*> m_edges_to;
public:
    Vertex(){}
    Vertex(int ID) : 
        m_ID(ID), m_height(0), m_excess_flow(0), m_type(Vertex_type::DEFAULT){}
    Vertex(int ID, int height, Vertex_type type) : 
        m_ID(ID), m_height(height), m_excess_flow(0), m_type(type){}

    int get_height() const {return m_height;}
    int get_excess_flow() const {return m_excess_flow;}
    int get_ID() const {return m_ID;}
    int get_type() const {return m_type;}
};

#endif // __VERTEX__