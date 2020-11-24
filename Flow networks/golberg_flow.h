#ifndef __GOLBER_FLOW__
#define __GOLBER_FLOW__

// Debug
#define NDEBUG

#ifdef NDEBUG
#include "golberg_flow_test.h"
#endif

#include <vector>

class Edge;
class Vertex;
class Golberg_flow;

enum Vertex_type {SOURCE, TARGET, DEFAULT};

class Vertex
{
private:
    int m_ID;
    int m_height;
    int m_excess_flow;
    Vertex_type m_type;
    std::vector<Edge*> m_edges_source;
    std::vector<Edge*> m_edges_target;
public:
    int get_height() const {return m_height;}
    int get_excess_flow() const {return m_excess_flow;}
    int get_ID() const {return m_ID;}
    int get_type() const {return m_type;}
};

class Edge
{
private:
    Vertex *m_star, *m_end;
    int m_flow;
    int m_reserve;
    int m_capacity;
public:
   Vertex* get_start() const {return m_star;}
   Vertex* get_end() const {return m_end;}
   int get_flow() const {return m_flow;}
   int get_reserve() const {return m_reserve;}
   int get_capacity() const {return m_capacity;}
};

class Golberg_flow
{
public:
    void add_edge(int from, int to, int capacity);
    int get_max_flow(int source, int target);
    int number_of_edges(){return m_edges.size();}
    int number_of_vertices(){return m_vertices.size();}
private:
    int m_index_source, m_index_target;
    std::vector<Edge> m_edges;
    std::vector<Vertex> m_vertices;

    Vertex* excess_flow_vertex();
    void push (Edge* edge);
    void relable (Vertex* vertex);
    void initialization();

};

#endif // __GOLBER_FLOW__