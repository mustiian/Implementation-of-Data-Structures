#ifndef __GOLBER_FLOW__
#define __GOLBER_FLOW__

#include "vertex.h"
#include "edge.h"

#define NDEBUG

#ifdef NDEBUG
#include "golberg_flow_test.h"
#endif

class Golberg_flow
{
public:
    Golberg_flow(){}
    Golberg_flow(int edges, int vertices, int source, int target);
    ~Golberg_flow(){}
    
    void add_edge(int from, int to, int capacity);
    int get_max_flow(int source, int target);
    int number_of_edges(){return m_edges.size();}
    int number_of_vertices(){return m_vertices.size();}
private:
    int m_index_source, m_index_target;
    std::vector<Edge> m_edges;
    std::vector<Vertex> m_vertices;

    Vertex& excess_flow_vertex();
    void push (Edge& edge);
    void relable (Vertex& vertex);
    void initialization();
};
/**
 * initialization constructor
 * 
 * @param  {int} edges    : Number of edges
 * @param  {int} vertices : Number of vertices
 * @param  {int} source   : Index of source vertex
 * @param  {int} target   : Index of target vertex
 */
Golberg_flow::Golberg_flow(int edges, int vertices, int source, int target) 
{
    m_edges.reserve(edges);
    m_vertices.reserve(vertices + 1);

    // Add vertices with unique ID, height and type
    for (int i = 0; i < vertices + 1; i++){
        if (i == source)
            m_vertices.push_back({i, vertices, Vertex_type::SOURCE});
        else if (i == target)
            m_vertices.push_back({i, 0, Vertex_type::TARGET});
        else
            m_vertices.push_back ({i});
    }

    m_index_source = source;
    m_index_target = target;
}
/**
 * Add new edge from the vertex to another vertex
 * 
 * @param  {int} from     : Index of the vertex where the edge starts from
 * @param  {int} to       : Index of the vertex where the edge comes to
 * @param  {int} capacity : Capacity of the edge
 */
void Golberg_flow::add_edge(int from, int to, int capacity) 
{
    m_edges.push_back({m_vertices[from], m_vertices[to], capacity});
    m_vertices[from].m_edges_from.push_back(&m_edges.back());
    m_vertices[to].m_edges_to.push_back(&m_edges.back());
}

#endif // __GOLBER_FLOW__